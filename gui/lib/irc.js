'use strict'

module.exports = function(blessed, core) {
    var chans = []
    core.on('open chan', function(name) {
        if (chans.indexOf(name) !== -1)
            return
        var log
        core.emit('open_win', name, function(core, api, _log) {
            log = _log
            chans.push(name)
            api.on('user input', function(text) {
                if (/^\//.test(text.trimLeft()))
                    core.emit('command', text)
                else
                    core.emit('send net', '/msg ' + name + ' ' + text.trimLeft())
                //log(blessed.escape(core.config.nick) + blessed.escape(text))
            })
            api.on('close', function() {
                chans = chans.filter(e => e !== name)
            })
        })
        core.on('info on ' + name, function(info) {
            log(info)
        })
        core.on('message on ' + name, function(name, text) {
            log('{' + core.config.color.c + '-fg}' + blessed.escape(name) + '{/}' + ': ' + blessed.escape(text))
        })
    })
    core.on('new message', function(chan) {
        if (!core.has_window(chan))
            core.emit('open chan', chan)
    })
}
