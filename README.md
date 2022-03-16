# SingleLevelCacheEmulator
 A single level cache emulator 

## Write Policy

This emulator uses write-through policy.

## Replacement Policy

This emulator uses FIFO replacement policy.

## How to build?

1. Clone the repository
2. Open /build directory
3. Execute build.sh script

## How to use?

1. Select size of memory, number of sets, number of ways. All in power of two.
2. Load instruction format: `load hexAddress data`
3. Read instruction format: `read hexAddress`

## Others

Main memory is initialized with random numbers