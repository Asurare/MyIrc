'use strict'

var blessed
var input
var text = ''
var pos = 0
var rpos = 0
var program = null

function update() {
    // if (text.length >= input.width) {
        if (rpos > input.width - 1) rpos = input.width - 1
        // if (rpos < 0) rpos = 0
        if (pos != rpos && rpos < 4) rpos = 4
        input.setContent(text.slice(pos - rpos, pos - rpos + input.width - 1))
    // } else {
    //     input.setContent(text)
    //     rpos = pos
    // }
    var lpos = input.lpos
    var cx = lpos.xi + input.ileft + rpos
    var cy = lpos.yi + input.itop
    if (cx !== program.x) {
        if (cx > program.x) {
            program.cuf(cx - program.x);
        } else if (cx < program.x) {
            program.cub(program.x - cx);
        }
    }
    if (cy !== program.y) {
        if (cy > program.y) {
            program.cud(cy - program.y);
        } else if (cy < program.y) {
            program.cuu(program.y - cy);
        }
    }
}

module.exports = function(bl, parent, core) {
    blessed = bl
    program = parent.screen.program
    parent.program.showCursor()
    const text_prompt = '> '
    var hist = []
    var hist_pos = -1
    var back_text = ''
    var prompt = blessed.text({
        parent: parent,
        width: text_prompt.length,
        height: 1,
        bottom: 0,
        content: text_prompt
    })
    input = blessed.text({
        parent: parent,
        width: '100%-' + text_prompt.length,
        height: 1,
        bottom: 0,
        left: text_prompt.length,
        content: text
    })
    core.on('input_left', function() {
        if (pos === 0 || !text.length)
            return
        pos--
        rpos--
        update()
    })
    core.on('input_right', function() {
        if (pos === text.length)
            return
        pos++
        rpos++
        update()
    })
    core.on('hist_up', function() {
        if (hist_pos === hist.length - 1)
            return
        if (hist_pos === -1)
            back_text = text
        text = hist[hist_pos + 1]
        pos = rpos = text.length
        hist_pos++
        update()
    })
    core.on('hist_down', function() {
        if (hist_pos === -1)
            return
        if (hist_pos === 0)
            text = back_text
        else
            text = hist[hist_pos - 1]
        pos = rpos = text.length
        hist_pos--
        update()
    })
    core.on('input_space', function() {
        api.add_text(' ')
    })
    core.on('input_enter', function() {
        core.emit('user input', text)
        if (hist[0] !== text)
            if (hist.unshift(text) > core.config.hist_length)
                hist.pop()
        text = ''
        hist_pos = -1
        pos  = 0
        rpos = 0
        update()
    })
    core.on('input_backspace', function() {
        if (pos === 0)
            return
        text = text.slice(0, pos - 1) + text.slice(pos, text.length)
        pos--
        rpos--
        update()
    })
    core.on('input_delete', function() {
        if (pos === text.length)
            return
        text = text.slice(0, pos) + text.slice(pos + 1, text.length)
        update()
    })
    core.on('input_home', function() {
        pos  = 0
        rpos = 0
        update()
    })
    core.on('input_end', function() {
        pos  = text.length
        rpos = text.length
        update()
    })
    var api = {
        set_text: function(str) {
            text = str
            pos  = str.length
            rpos = str.length
            hist_pos = -1
            update()
        },
        add_text: function(str) {
            text = text.slice(0, pos) + str + text.slice(pos, text.length)
            pos  += str.length
            rpos += str.length
            hist_pos = -1
            update()
        },
        rm_text: function() {
            text = ''
            pos  = 0
            rpos = 0
            hist_pos = -1
            update()
        },
        update: update
    }
    return api
}
