'use strict'

module.exports = function(blessed, parent, core) {
    const window = require('./window.js')(blessed, core)
    const tab = require('./tab.js')(blessed, parent, core)
    var active_win = null
    var win_box = blessed.box({
        parent: parent,
        width: '100%',
        height: '100%-2',
        top: 1,
        left: 0
    })
    function resize_box() {
        win_box.setContent('|'.repeat(win_box.width * win_box.height))
    }
    resize_box()
    win_box.on('resize', resize_box)
    var windows = []
    core.on('user input', function(text) {
        api.log(text)
    })
    core.on('open_win', function(name, func) {
        api.open_win(name, func)
    })
    core.on('scroll_up', function() {
        active_win.api.scroll(-1)
    })
    core.on('scroll_down', function() {
        active_win.api.scroll(1)
    })
    core.on('dispatch', function(event, args) {
        if (active_win)
            active_win.api.emit()
    })
    core.on('close window', function() {
        if (active_win && active_win.name[0] !== '_') {
            // console.error('closing ' + active_win.name)
            var index = windows.indexOf(active_win)
            // console.error('index ' + index)
            windows = windows.filter(e => e !== active_win)
            tab.remove(active_win.name)
            core.emit('command', 'part ' + active_win.name)
            active_win.box.hide()
            active_win.box.detach()
            active_win = windows[index === windows.length ? index - 1 : index]
            active_win.box.show()
            // console.error('new win ' + active_win.name)
            api.focus(active_win.name)
        }
    })
    var api = {}
    api.open_win = function(name, func) {
        var obj = {name}
        obj.box = blessed.box({
            parent: win_box,
            width: '100%',
            height: '100%',
            top: 0,
            left: 0
        })
        obj.api = window(obj.box, func)
        obj.api.set_status(name)
        windows.push(obj)
        tab.add(name, function() {
            api.focus(name)
        })
        api.focus(name)
    }
    api.focus = function(name) {
        if (!name)
            return false
        var found = windows.find(e => e.name === name)
        if (found) {
            if (active_win)
                active_win.box.hide()
            found.box.show()
            active_win = found
            tab.update(name)
        }
        return !!found
    }
    core.has_window =
    api.has = function(name) {
        if (!name)
            return false
        return windows.find(e => e.name == name)
    }
    api.log = function(message, name) {
        var found
        if (name)
            found = windows.find(e => e.name == name)
        else
            found = active_win
        if (found)
            found.api.emit('user input', message)
        return !!found
    }
    api.close_win = function(name) {
    }
    return api
}
