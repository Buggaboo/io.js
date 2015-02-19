'use strict';

/**
 * 
 * See `util.format` to do %s, %d, %j string formatting.
 * 
 * For example:
 *
 * var util = require('util'),
 *     logcat = require('android_logcat');
 * 
 * var TAG = 'script.js';
 * 
 * logcat.d(TAG, util.format('%s: %j', 'json', { 'a' : 'b' }));
 */ 

/*    
    ANDROID_LOG_DEBUG = 3,
    ANDROID_LOG_INFO,
    ANDROID_LOG_WARN,
    ANDROID_LOG_ERROR,
    ANDROID_LOG_FATAL = 7,    
*/

const binding = process.binding('os');
// exports.android_logcat = binding.__android_logcat; // test


exports.android_logcat = function () {
    return {
        __base : function (priority, tag, input) { binding.__android_logcat(priority, tag, input); },

        d : function(tag, input) { __base(3, tag, input); },
        i : function(tag, input) { __base(4, tag, input); },
        w : function(tag, input) { __base(5, tag, input); },
        e : function(tag, input) { __base(6, tag, input); },
        f : function(tag, input) { __base(7, tag, input); },
    }
};

