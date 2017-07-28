'use strict'
var buff = {}

module.exports = {
	'^:(\\w+)!@srv \\w+ PRIVMSG ([#&+]?\\w*) :(.*)': function(core, str, match) {
		core.emit('new_message', match[2])
		core.emit('message on ' + match[2], match[1], match[3])
	}, //msg succesfully send
	'^:\\w+![0-9.]* NICK ': function(core, str) {
		core.emit('command result', `info : change name to {${core.config.color.c}-fg}` + str + `{/${core.config.color.c}-fg} `)
		core.config.nick = str
	}, //Nickname succesfully changed
	'^(\\w+): JOIN :([#&+]\\w*)': function(core, str, match) {
		core.emit('open chan', match[2])
		core.emit('user join chan', match[1], match[2])
		core.emit('info on ' + match[2], '{center} -- {' + core.config.color.c + '-fg}' + match[1] + '{/} join the channel --{/center}')
	}, //Channel succesfully joined
	'^(\\w+) PART ([#&+]\\w*)': function(core, str, match) {
		core.emit('new_message', match[2])
		core.emit('user leave chan', match[1], match[2])
		core.emit('info on ' + match[2], '{center} -- {' + core.config.color.c + '-fg}' + match[1] + '{/} leave the channel --{/center}')
	}, //Channel succesfully quit
	'^QUIT': function(core, str) {}, //Server succesfully quit
	'^0': {
		'^0': {
			'^[1-3] ': function(core, str) {
				core.emit('command result', str)
			},
			'^4 ': function(core, str) {
				core.emit('command result', str)
				core.emit('command result', 'info : connection succesfull')
				core.emit('connected')
			} //Connection succesfully made
		}
	},
	'^1': {

	},
	'^2': {

	},
	'^3': {
		'^6': {
			'^6': function(core, str) {} //Names successfully done
		},
		'^2': {
			'^3': function(core, str) {} //List successfully done
		},
		'^9': {
			'^4': function(core, str) {} //Users successfully done
		}
	},
	'^4': function(core, str) {
		core.emit('command result', 'recieved error 4' + str.slice(0, 2) + ' (' + str.slice(3) + ') from server')
	} //Error in last command
}
