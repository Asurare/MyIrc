'use strict'

const blessed = require('blessed')
const screen = blessed.screen({
    smartCSR: true,
    autoPadding: false,
    warnings: true
})

var log = blessed.log({
    parent: screen
})

screen.on('keypress', function(key, obj) {
    if (obj.full == 'C-q')
        screen.destroy()
    log.log(key, obj)
})
