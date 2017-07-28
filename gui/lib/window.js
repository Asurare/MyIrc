'use strict'

var blessed

module.exports = function(blessed, core) {
    const EventEmitter = require('events')
    return function(parent, func) {
        var status_str = ''
        var message = blessed.log({
            parent: parent,
            width: '100%',
            height: '100%-1',
            // border: 'line',
            tags: true,
            scrollback: 100,
            scrollbar: {
                ch: ' ',
                track: {
                    bg: 'gray'
                },
                style: {
                    inverse: true
                }
            },
            top: 0,
            left: 0
        })
        var status = blessed.text({
            parent: parent,
            width: '100%',
            height: 1,
            bottom: 0,
            style: {
                bg: 'gray'
            }
        })
        parent.on('resize', function() {
            api.set_status(status_str)
        })
        status.setContent('-'.repeat(status.width))
        var api = new EventEmitter()
        api.set_status = function(str) {
            status_str = str
            var new_str = '-- ' + str.slice(0, status.width - 3) + ' ' + '-'.repeat(status.width - 4 - str.length)
            status.setContent(new_str.slice(0, status.width))
        }
        api.focus = function(bool) {
            status.style.bg = bool ? 'gray' : 'black'
            status.render()
        }
        api.refresh_users = function(list) {
        }
        api.scroll = function(offset) {
            message.scroll(offset)
        }
        func(core, api, function(str) {
            message.log(str)
        })
        return api
    }
}
