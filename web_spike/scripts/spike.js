"use strict";

var gifFrames = require('gif-frames');
var fs = require('fs');

gifFrames({ url: './images/middleparrot.gif', frames: 'all' }).then(function (frameData) {
	console.log(frameData);

});
