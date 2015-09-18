'use strict';

/**
 * 
 * See `util.format` to do %s, %d, %j string formatting.
 * 
 * For example:
 *
 * var util = require('util'),
 *   android = require('android');

 * var logcat = android.logcat,
 *   android_logcat = android.android_logcat;

 * var TAG = 'script.js';

 * android_logcat(3, TAG, util.format('%s: %j', 'json', { 'a' : 'b' }));
 * android_logcat(4, TAG, util.format('%s: %j', 'json', { 'a' : 'b' }));

 * logcat.d(TAG, util.format('%s: %j', 'json', { 'c' : 'd' }));
 * logcat.i(TAG, util.format('%s: %j', 'json', { 'c' : 'd' }));
 */ 

/*    
    ANDROID_LOG_DEBUG = 3,
    ANDROID_LOG_INFO,
    ANDROID_LOG_WARN,
    ANDROID_LOG_ERROR,
    ANDROID_LOG_FATAL = 7,    
*/

const binding = process.binding('android');

exports.android_logcat = binding.android_logcat;

exports.logcat = {};

var __base = function (priority, tag, input) { binding.android_logcat(priority, tag, input); }

exports.logcat.d = function(tag, input) { __base(3, tag, input); }
exports.logcat.i = function(tag, input) { __base(4, tag, input); }
exports.logcat.w = function(tag, input) { __base(5, tag, input); }
exports.logcat.e = function(tag, input) { __base(6, tag, input); }
exports.logcat.f = function(tag, input) { __base(7, tag, input); }

