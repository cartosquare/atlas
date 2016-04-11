{
    "includes":
    [
        'common.gypi',
    ],
  
    'targets':
    [
        {
            'target_name': 'core',
            'type': 'static_library',
            'includes':
            [
                'core.gypi'
            ],
            
            'direct_dependent_settings': {
                'include_dirs':
                [
                    '../include',
                ],
            },
            
            'link_settings':
            {
                'conditions':
                [
                    ['OS == "mac"', {
                    'libraries':
                        [
                            '$(SDKROOT)/System/Library/Frameworks/Cocoa.framework',
                            '$(SDKROOT)/System/Library/Frameworks/Foundation.framework',
                            '$(SDKROOT)/System/Library/Frameworks/CoreVideo.framework',
                            '$(SDKROOT)/System/Library/Frameworks/IOKit.framework',
                        ],
                        'cflags_cc': [ '-std=c++11' ],
                        "xcode_settings":
                        {
                            'OTHER_CPLUSPLUSFLAGS' : ['-std=c++11','-stdlib=libc++',],
                            'OTHER_LDFLAGS':
                            [
                                '-stdlib=libc++',
                                '/usr/local/lib/libprotobuf-lite.a',
                                '/usr/local/lib/libboost_system-mt.a',
                                '/usr/local/lib/libboost_thread-mt.a',
                                '/usr/local/lib/libboost_filesystem-mt.a',
                                '/usr/local/lib/libboost_date_time-mt.a',
                                '/usr/local/lib/libboost_timer-mt.a',
                                '/usr/local/lib/libboost_chrono-mt.a',
                                '/usr/local/lib/libboost_log-mt.a',
                                '/usr/local/lib/libboost_log_setup-mt.a',
                                '/usr/local/lib/libboost_regex-mt.a',
                            ],
                        },
                }],
                    ['OS == "linux"', {
                    'libraries':
                    [
                        '-I/usr/local/include',
                        '-L/usr/local/lib',
                        '-L<(boost_root)/stage/lib',
                        '-L/usr/lib64',
                        '-L<(boost_root)/include',
                        '-lboost_regex-mt',
                        '-lboost_chrono-mt',
                        '-lboost_system-mt',
                        '-lboost_thread-mt',
                        '-lboost_date_time-mt',
                        '-lboost_timer-mt',
                        '-lboost_filesystem-mt',
                        '-lboost_log_setup-mt',
                        '-lboost_log-mt',
                  ]
              }],
                ],
            },
        },
    ],
}
