'use strict'

const EventEmitter = require('events')
const blessed = require('blessed')
const config = require('./config.json')

var screen = blessed.screen({
    smartCSR: true,
    autoPadding: false,
    warnings: true,
    cursor: config.cursor
})
var arg = require('yargs-parser')(process.argv.slice(2), {
    alias: {
        port: ['p'],
        log: ['l']
    },
    'default': {
        port: 80,
        log: false
    },
    boolean: [
        'log'
    ],
    number: [
        'port'
    ]
})

if (arg.h) {
    console.log('node gui [-p num] [address[:port]]')
    process.exit(0)
}

var api = new EventEmitter()
api.arg = arg
api.config = config
var input = require('./lib/input.js')(blessed, screen, api)
var win_manager = require('./lib/win_manager.js')(blessed, screen, api)
var network = require('./lib/network.js')(blessed, api)
var command = require('./lib/command.js')(blessed, api)
var irc = require('./lib/irc.js')(blessed, api)

api.on('quit_app', function() {
    screen.destroy()
    api.emit('quit net')
})

screen.on('keypress', function(key, obj) {
    if (config.control[obj.full])
        api.emit(config.control[obj.full], key, obj)
    else if (obj.ch || obj.shift || obj.name == key)
        input.add_text(key)
    else
        api.emit('keypress', key, obj)
    screen.render()
})
screen.on('destroy', function() {
    if (screen.program.has('cnorm')) screen.program.put.cnorm()
})
screen.on('resize', function() {
    input.update()
})

screen.render()
screen.program.hideCursor()
input.rm_text() // to pos the cursor
screen.program.showCursor()
