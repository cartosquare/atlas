{
     "includes":
    [
        'common.gypi',
    ],
    'targets': 
    [
        {
            'target_name': 'tests',
            'type': 'executable',
            'includes': 
            [
                'tests.gypi'
            ],
            'conditions':
            [
                ['open_filter', {
                    'sources':
                    [
                     '../tests/cases/expression_test.cpp',
                    ],
                }],
	    ],
            'dependencies':
            [
                'core.gyp:core',
            ],
            'include_dirs':
            [
                '../tests/main',
                '../tests/cases',
            ],
        }
    ],
}
