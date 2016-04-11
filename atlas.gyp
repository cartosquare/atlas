# Build EVERYTHING.
{
    'targets':
    [
    {
        'target_name': 'atlas',
        'type': 'none',
        'dependencies':
        [
        'gyp/core.gyp:*',
        'gyp/tests.gyp:*',
        ],
        'sources':
        [
        'atlas.gyp',
        'gen_xcode.sh',
        ],
    },
    ],
}
