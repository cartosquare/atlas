{
    'variables':
    {
        'boost_root': '../3rd/boost_1_58_0',
        'open_filter': 0,
        'open_log': 1,
    },
    'target_defaults': {
        'defines': [
        '_USE_MATH_DEFINES',
        'BOOST_REGEX_HAS_ICU',
        ],
        
        'includes': [
        'common_conditions.gypi',
        ],

        'conditions':
        [
        ['open_filter', {
            'defines':
            [
            'FILTER_GEOTAG',
            ],
        }],
        ['open_log', {
            'defines':
            [
            'OPEN_LOG',
            ],
        }],
        ['OS == "linux"', {
            'defines':
            [
            'BOOST_LOG_DYN_LINK',
            ],
        }],
	],
        
        'include_dirs':
        [
        '../include/',
        '../3rd/boost_1_58_0',
        '/usr/local/include',
        ],
        'cflags': [
        '-fPIC',
        ],
        'cflags_cc!': [ '-fno-rtti', '-fno-exceptions',],
    }, # end 'target_defaults'
}
