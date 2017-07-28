'use strict'

module.exports = function(blessed, core) {
    var log
    core.emit('open_win', '_console', function(core, _api, _log) {
        log = _log
        _api.on('user input', function(text) {
            api.exec(text)
        })
    })
    core.on('command result', function(text) {
        log(blessed.escape(text))
    })
    core.on('command', function(text) {
        api.exec(text)
    })
    var api = {}
    api.exec = function(text) {
        if (text === '')
            return
        text = text.trimLeft()
        log('> ' + blessed.escape(text.replace(/^\//, '')))
        if (/^server/.test(text.replace(/^\//, '')))
            core.connect(...(text.split(' ').filter((e, i) => i)))
        else
            core.emit('send net', text.replace(/^[^/]/, '/$&'))
    }
    return api
}
