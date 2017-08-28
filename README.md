# kut
[![Build Status](https://travis-ci.org/koichi-murakami/kut.svg?branch=master)](https://travis-ci.org/koichi-murakami/kut)

Copyright (c) 2017, Koichi Murakami

A set of misc. utilities

* `jparser` : Extended JSON parser (JSON5)
* `thistory` : Time counting and event history in app

## Version
* [Releases](https://github.com/koichi-murakami/kut/releases)
* [Issues](https://github.com/koichi-murakami/kut/issues)

## Code samples - how to work
### jparser
Extended JSON parser (JSON5).
Accessing parameters with key-values map.
Keys are structured with "/" like Unix directory traversal.

~~~~
  JsonParser* jparser = JsonParser::GetJsonParser();
  bool qload = jparser-> LoadFile(config_file);

  // dump parsed data
  jparser-> DumpAll();

  // get double vaule with a key string
  std::cout << "@@@ Geometry/size = "
            << jparser-> GetDoubleValue("Geometry/size") << std::endl;
~~~~


An example of JSON5 data that can be parsed with `jparser`.
~~~~
{
  // global parameters
  yesorno : true,
  yesorno_list : [ true, false],
  // -----------------------------------------------------------------
  // primary setting
  "Primary" : {
    // primary type (gun / beam)
    type : 'gun',
    number : 100,

    // particle starting position (x,y,z) in cm (z >= -100)
    position : [ 5., +.1, +100. ],

    legend : ["x1", "y2", "z3"],

  },
  // -----------------------------------------------------------------
  // geometry setup
  Geometry : {
    /* geometry size */
    size : 20.0,

    segment : [5, 105, 25],

    // position in different namespace
    position : [ 1., 1., 0. ],

    // sub objects
    type : {
      name : "calorimeter A",
    },

  },
}
~~~~

The above data is processed to the following data structure.
~~~~
@@@ dump JSON data
Geometry :
  position : [1,1,0]
  segment : [5,105,25]
  size : 20
  type :
    name : "calorimeter A"
Primary :
  legend : ["x1","y2","z3"]
  number : 100
  position : [5,0.10000000000000001,100]
  type : "gun"
yesorno : true
yesorno_list : [true,false]
~~~~

### thistory
Utility tools for time counting and event history.

~~~~
  TimeHistory* gtimer = TimeHistory::GetTimeHistory();

  // show current time with a message
  gtimer-> ShowClock("some message...");

  // take split for event-1
  gtimer-> TakeSplit("event-1");

  // get time of split
  double t1 = gtimer-> GetTime("event-1");

  // show all histories
  gtimer-> ShowAllHistories();
~~~~

## Dependencies

The following software is used for the library.

* [picojson](https://github.com/kazuho/picojson) : 1.3.0 (embedded)
* [CppUTest](https://github.com/cpputest/cpputest) : used for unit testing

## License
BSD 2-Clause License

Copyright (c) 2017, Koichi Murakami
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The above copyright and license notice applies to distributions of
kut software in source and binary form.  Some source files contain
additional notices of original copyright by their contributors;
see each source for details.
