#!/usr/bin/env node
var c = require('/home/chris/Dropbox/cbackend/build/Release/cbackend.node');
console.log('c.hello', c.hello);
console.log('c.get_groups()', c.get_groups());
console.log("c.get_subgroups('72')", c.get_subgroups('72'));
console.log("c.get_stock_by_group('72')", c.get_stock_by_group('72'));
