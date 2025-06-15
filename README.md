src/
├── core/
│   ├── data_management.c      # initialize_push_swap_data, allocate_and_init_stack
│   ├── memory_management.c    # cleanup_and_exit_with_error, release_allocated_memory
│   └── stack_operations.c     # stack utility functions
├── parsing/
│   ├── input_validation.c     # validate_numeric_argument, verify_stack_is_sorted
│   ├── number_conversion.c    # convert_numbers_to_ranks, efficient_sort
│   └── duplicate_detection.c  # detect_duplicates_optimized, detect_duplicates_with_sorting
├── operations/
│   ├── push_operations.c      # pa, pb, push
│   ├── rotate_operations.c    # ra, rb, rr, rotate
│   ├── reverse_rotate_ops.c   # rra, rrb, rrr, r_rotate
│   ├── swap_operations.c      # sa, sb, ss, swap
│   └── operation_tracking.c   # save_op, print_operations, op_to_string
├── algorithms/
│   ├── sorting_strategy.c     # main sort entry point
│   ├── chunk_algorithm/
│   │   ├── chunk_manager.c    # chunk utilities and management
│   │   ├── chunk_splitter.c   # chunk splitting logic
│   │   └── recursive_sort.c   # main chunk sorting algorithm
│   └── small_sorts/
│       ├── two_element_sort.c
│       ├── three_element_sort.c
│       └── small_array_sorts.c
├── optimizations/
│   ├── pattern_recognition/
│   │   ├── easy_patterns.c    # easy_sort functionality
│   │   ├── consecutive_detect.c # split_max_reduction, is_consecutive
│   │   └── positioning_opts.c  # chunk_to_the_top
│   └── post_processing/
│       ├── operation_merging.c # merge operations (rr, ss, etc.)
│       ├── neutral_elimination.c # eliminate redundant operations
│       └── pattern_optimization.c # optimize operation sequences
├── movement/
│   ├── element_positioning.c  # move_from_to and variants
│   └── location_utilities.c   # loc_to_stack helpers
├── push_swap/
│   ├── main.c
│   └── program_controller.c   # high-level program flow
├── checker/
│   ├── checker_main.c
│   ├── operation_reader.c     # read_op, string_to_op
│   ├── checker_operations.c   # checker-specific operation wrappers
│   └── validation.c           # test_sort
└── shared/
    ├── constants.h            # shared constants and defines
    └── error_handling.c       # common error handling