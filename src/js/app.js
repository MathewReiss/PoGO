var Clay = require('pebble-clay');
var clayConfig = require('./config');
var customClay = require('./custom-clay');
var userData = {token: 'abc123'};
var clay = new Clay(clayConfig, customClay, {userData: userData});