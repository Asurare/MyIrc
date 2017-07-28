'use strict'


module.exports = function(blessed, core) {
    const EventEmitter = require('events')
    return function container (parent) {
        var boxes
        var api = new EventEmitter()
        api.move = function() {}
        api.focus = function() {}
        api.split = function(way) {
            var vertical = (way === 'vertical')
            boxes = [
                blessed.box({
                    parent: parent,
                    width: vertical ? '100%' : '50%',
                    height: vertical ? '50%' : '100%',
                }),
                blessed.box({
                    parent: parent,
                    width: vertical ? '100%' : '50%-1',
                    height: vertical ? '50%-1' : '100%',
                    right: vertical ? undefined : 0,
                    bottom: vertical ? 0 : undefined

                })
            ]
        }
        api.getfocus = function() {}
        return api
    }
}
