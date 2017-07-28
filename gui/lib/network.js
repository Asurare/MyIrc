'use strict'

const cp = require('child_process')
const EventEmitter = require('events')
const readline = require('readline')
const SplitStream = require('split-stream')
const parser = require('./parse.js')

function parse(parser, str, core) {
    var match
    for (let i in parser) {
        if ((match = RegExp(i).exec(str)) !== null) {
            if (parser[i] instanceof Function) {
                parser[i](core, str.slice(match[0].length), match)
                return true
            }
            else
                return parse(parser[i], str.slice(match[0].length), core)
        }
    }
    return false
}

module.exports = function(blessed, core) {
    var log, net, connected = false
    var net_log = function(text) {
        if (net) {
            log('=> ' + blessed.escape(text))
            net.stdin.write(text)
        } else
            log('XX ' + blessed.escape(text))
    }
    core.emit('open_win', '_net', function(core, api, _log) {
        log = _log
        api.on('user input', net_log)
    })
    core.on('quit net', function() {
        if (net)
            net.kill()
        net = null
    })
    core.on('send net', net_log)
    core.on('connected', function() {
        connected = true
    })
    core.connect = function(address, port) {
        if (!address)
            return
        if (connected)
            core.emit('quit net')
        address = address == 'localhost' ? '127.0.0.1' : address
        port = port || core.arg.p
        log(`INFO : establishing connection on ${address}:${port}`)
        if (!net)
            net = cp.spawn('../client')
        var stdout = SplitStream.create({splitStr: '\n'})
        net.stdout.pipe(stdout)
        stdout.on('data', function(line) {
            if (line == '\r')
                return
            line = line.replace('\r', '')
            parse(parser, line, core)
            log('<- ' + blessed.escape(line))
        })
        var stderr = SplitStream.create({splitStr: '\n'})
        net.stderr.pipe(stderr)
        stderr.on('data', function(line) {
            if (line === '\r')
                return
            log('{red-fg}<- ' + blessed.escape(line.replace('\r', '') + '{/red-fg}'))
        })
        net.on('exit', function() {
            net = null
            log('INFO : connection terminated')
            connected = false
        })
        net_log(`/server ${address} ${port}`)
        net_log(`/nick ${core.config.nick}`)
    }
}
