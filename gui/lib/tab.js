'use strict'

module.exports = function(bl, parent, core) {
    const EventEmitter = require('events')
    var bar = bl.listbar({
        parent: parent,
        height: 1,
        style: {
            bg: 'white',
            prefix: {
                fg: core.config.color.c
            },
            item: {
                fg: 'black',
                bg: 'white',
            },
            selected: {
                fg: 'white',
                bg: 'gray'
            }
        },
        autoCommandKeys: false
    })
    core.on('tab_next', function() {
        api.move(1)
    })
    core.on('tab_prev', function() {
        api.move(-1)
    })
    var names = []
    var api = new EventEmitter()
    api.add = function(name, func) {
        bar.add(name, func)
        names.push(name)
    }
    api.remove = function(name) {
        bar.removeItem(names.indexOf(name))
        names = names.filter(e => e !== name)
    }
    api.move = function(offset) {
        var old = bar.selected
        bar.move(offset)
        bar.selectTab(bar.selected)
    }
    api.select = function(index) {
        bar.select(index)
        bar.selectTab(bar.selected)
    }
    api.update = function(name) {
        var old = bar.selected
        bar.select(names.indexOf(name))
        bar.screen.render()
    }
    return api
}
