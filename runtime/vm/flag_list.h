// Copyright (c) 2012, the Dart project authors.  Please see the AUTHORS file
// for details. All rights reserved. Use of this source code is governed by a
// BSD-style license that can be found in the LICENSE file.

#ifndef RUNTIME_VM_FLAG_LIST_H_
#define RUNTIME_VM_FLAG_LIST_H_

// Don't use USING_DBC outside of this file.
#if defined(TARGET_ARCH_DBC)
#define USING_DBC true
#else
#define USING_DBC false
#endif

// Don't use USING_KBC outside of this file.
#if defined(DART_USE_INTERPRETER)
#define USING_KBC true
#else
#define USING_KBC false
#endif

// Don't use USING_MULTICORE outside of this file.
#if defined(ARCH_IS_MULTI_CORE)
#define USING_MULTICORE true
#else
#define USING_MULTICORE false
#endif

// Don't use USING_PRODUCT outside of this file.
#if defined(PRODUCT)
#define USING_PRODUCT true
#else
#define USING_PRODUCT false
#endif

#if defined(DART_PRECOMPILED_RUNTIME)
constexpr bool kDartPrecompiledRuntime = true;
#else
constexpr bool kDartPrecompiledRuntime = false;
#endif

// List of all flags in the VM.
// Flags can be one of three categories:
// * P roduct flags: Can be set in any of the deployment modes, including in
//   production.
// * R elease flags: Generally available flags except when building product.
// * D ebug flags: Can only be set in debug VMs, which also have C++ assertions
//   enabled.
// * pre C ompile flags: Generally available flags except when building product
//   or precompiled runtime.
//
// Usage:
//   P(name, type, default_value, comment)
//   R(name, product_value, type, default_value, comment)
//   D(name, type, default_value, comment)
//   C(name, precompiled_value, product_value, type, default_value, comment)
#define FLAG_LIST(P, R, D, C)                                                  \
  P(abort_on_oom, bool, false,                                                 \
    "Abort if memory allocation fails - use only with --old-gen-heap-size")    \
  C(async_debugger, false, false, bool, true,                                  \
    "Debugger support async functions.")                                       \
  P(background_compilation, bool, USING_MULTICORE,                             \
    "Run optimizing compilation in background")                                \
  R(background_compilation_stop_alot, false, bool, false,                      \
    "Stress test system: stop background compiler often.")                     \
  P(causal_async_stacks, bool, !USING_PRODUCT, "Improved async stacks")        \
  P(collect_code, bool, true, "Attempt to GC infrequently used code.")         \
  P(collect_dynamic_function_names, bool, true,                                \
    "Collects all dynamic function names to identify unique targets")          \
  P(compactor_tasks, int, 2,                                                   \
    "The number of tasks to use for parallel compaction.")                     \
  P(concurrent_sweep, bool, USING_MULTICORE,                                   \
    "Concurrent sweep for old generation.")                                    \
  R(dedup_instructions, true, bool, false,                                     \
    "Canonicalize instructions when precompiling.")                            \
  C(deoptimize_alot, false, false, bool, false,                                \
    "Deoptimizes we are about to return to Dart code from native entries.")    \
  C(deoptimize_every, 0, 0, int, 0,                                            \
    "Deoptimize on every N stack overflow checks")                             \
  R(disable_alloc_stubs_after_gc, false, bool, false, "Stress testing flag.")  \
  R(disassemble, false, bool, false, "Disassemble dart code.")                 \
  R(disassemble_optimized, false, bool, false, "Disassemble optimized code.")  \
  R(dump_megamorphic_stats, false, bool, false,                                \
    "Dump megamorphic cache statistics")                                       \
  R(dump_symbol_stats, false, bool, false, "Dump symbol table statistics")     \
  P(dwarf_stack_traces, bool, false,                                           \
    "Emit DWARF line number and inlining info"                                 \
    "in dylib snapshots and don't symbolize stack traces.")                    \
  R(enable_asserts, false, bool, false, "Enable assert statements.")           \
  P(enable_kernel_expression_compilation, bool, true,                          \
    "Compile expressions with the Kernel front-end.")                          \
  P(enable_mirrors, bool, true,                                                \
    "Disable to make importing dart:mirrors an error.")                        \
  R(enable_type_checks, false, bool, false, "Enable type checks.")             \
  R(error_on_bad_override, false, bool, false,                                 \
    "Report error for bad overrides. Ignored in strong mode.")                 \
  R(error_on_bad_type, false, bool, false,                                     \
    "Report error for malformed types.")                                       \
  P(fields_may_be_reset, bool, false,                                          \
    "Don't optimize away static field initialization")                         \
  C(force_clone_compiler_objects, false, false, bool, false,                   \
    "Force cloning of objects needed in compiler (ICData and Field).")         \
  R(gc_at_alloc, false, bool, false, "GC at every allocation.")                \
  P(getter_setter_ratio, int, 13,                                              \
    "Ratio of getter/setter usage used for double field unboxing heuristics")  \
  P(guess_icdata_cid, bool, true,                                              \
    "Artificially create type feedback for arithmetic etc. operations")        \
  P(huge_method_cutoff_in_tokens, int, 20000,                                  \
    "Huge method cutoff in tokens: Disables optimizations for huge methods.")  \
  P(idle_timeout_micros, int, 1000 * kMicrosecondsPerMillisecond,              \
    "Consider thread pool isolates for idle tasks after this long.")           \
  P(idle_duration_micros, int, 500 * kMicrosecondsPerMillisecond,              \
    "Allow idle tasks to run for this long.")                                  \
  P(interpret_irregexp, bool, USING_DBC, "Use irregexp bytecode interpreter")  \
  P(lazy_dispatchers, bool, true, "Generate dispatchers lazily")               \
  P(link_natives_lazily, bool, false, "Link native calls lazily")              \
  C(load_deferred_eagerly, true, true, bool, false,                            \
    "Load deferred libraries eagerly.")                                        \
  R(log_marker_tasks, false, bool, false,                                      \
    "Log debugging information for old gen GC marking tasks.")                 \
  R(marker_tasks, USING_MULTICORE ? 2 : 0, int, USING_MULTICORE ? 2 : 0,       \
    "The number of tasks to spawn during old gen GC marking (0 means "         \
    "perform all marking on main thread).")                                    \
  P(max_polymorphic_checks, int, 4,                                            \
    "Maximum number of polymorphic check, otherwise it is megamorphic.")       \
  P(max_equality_polymorphic_checks, int, 32,                                  \
    "Maximum number of polymorphic checks in equality operator,")              \
  P(new_gen_semi_max_size, int, (kWordSize <= 4) ? 8 : 16,                     \
    "Max size of new gen semi space in MB")                                    \
  P(new_gen_semi_initial_size, int, (kWordSize <= 4) ? 1 : 2,                  \
    "Initial size of new gen semi space in MB")                                \
  P(omit_strong_type_checks, bool, false, "Omit strong mode type checks.")     \
  P(optimization_counter_threshold, int, 30000,                                \
    "Function's usage-counter value before it is optimized, -1 means never")   \
  P(old_gen_heap_size, int, kDefaultMaxOldGenHeapSize,                         \
    "Max size of old gen heap size in MB, or 0 for unlimited,"                 \
    "e.g: --old_gen_heap_size=1024 allows up to 1024MB old gen heap")          \
  R(pause_isolates_on_start, false, bool, false,                               \
    "Pause isolates before starting.")                                         \
  R(pause_isolates_on_exit, false, bool, false, "Pause isolates exiting.")     \
  R(pause_isolates_on_unhandled_exceptions, false, bool, false,                \
    "Pause isolates on unhandled exceptions.")                                 \
  P(polymorphic_with_deopt, bool, true,                                        \
    "Polymorphic calls with deoptimization / megamorphic call")                \
  P(precompiled_mode, bool, false, "Precompilation compiler mode")             \
  P(print_precompiler_entry_points, charp, NULL,                               \
    "Print entry points and info about recognized methods used by "            \
    "precompiler.")                                                            \
  P(print_snapshot_sizes, bool, false, "Print sizes of generated snapshots.")  \
  P(print_snapshot_sizes_verbose, bool, false,                                 \
    "Print cluster sizes of generated snapshots.")                             \
  P(print_benchmarking_metrics, bool, false,                                   \
    "Print additional memory and latency metrics for benchmarking.")           \
  R(print_ssa_liveranges, false, bool, false,                                  \
    "Print live ranges after allocation.")                                     \
  R(print_stacktrace_at_api_error, false, bool, false,                         \
    "Attempt to print a native stack trace when an API error is created.")     \
  C(print_stop_message, false, false, bool, false, "Print stop message.")      \
  D(print_variable_descriptors, bool, false,                                   \
    "Print variable descriptors in disassembly.")                              \
  R(profiler, false, bool, false, "Enable the profiler.")                      \
  R(profiler_native_memory, false, bool, false,                                \
    "Enable native memory statistic collection.")                              \
  P(reify_generic_functions, bool, false,                                      \
    "Enable reification of generic functions (not yet supported).")            \
  P(reorder_basic_blocks, bool, true, "Reorder basic blocks")                  \
  C(stress_async_stacks, false, false, bool, false,                            \
    "Stress test async stack traces")                                          \
  P(strong, bool, false, "Enable strong mode.")                                \
  P(sync_async, bool, false, "Start `async` functions synchronously.")         \
  R(support_ast_printer, false, bool, true, "Support the AST printer.")        \
  R(support_compiler_stats, false, bool, true, "Support compiler stats.")      \
  R(support_disassembler, false, bool, true, "Support the disassembler.")      \
  R(support_il_printer, false, bool, true, "Support the IL printer.")          \
  C(support_reload, false, false, bool, true, "Support isolate reload.")       \
  R(support_service, false, bool, true, "Support the service protocol.")       \
  R(support_timeline, false, bool, true, "Support timeline.")                  \
  D(trace_cha, bool, false, "Trace CHA operations")                            \
  D(trace_field_guards, bool, false, "Trace changes in field's cids.")         \
  C(trace_irregexp, false, false, bool, false, "Trace irregexps.")             \
  D(trace_isolates, bool, false, "Trace isolate creation and shut down.")      \
  D(trace_handles, bool, false, "Traces allocation of handles.")               \
  D(trace_kernel_binary, bool, false, "Trace Kernel reader/writer.")           \
  D(trace_optimization, bool, false, "Print optimization details.")            \
  R(trace_profiler, false, bool, false, "Profiler trace")                      \
  D(trace_profiler_verbose, bool, false, "Verbose profiler trace")             \
  D(trace_ssa_allocator, bool, false, "Trace register allocation over SSA.")   \
  P(trace_strong_mode_types, bool, false,                                      \
    "Trace optimizations based on strong mode types.")                         \
  D(trace_zones, bool, false, "Traces allocation sizes in the zone.")          \
  P(truncating_left_shift, bool, true,                                         \
    "Optimize left shift to truncate if possible")                             \
  P(use_compactor, bool, false, "Compact the heap during old-space GC.")       \
  P(use_cha_deopt, bool, true,                                                 \
    "Use class hierarchy analysis even if it can cause deoptimization.")       \
  P(use_field_guards, bool, !USING_DBC && !USING_KBC,                          \
    "Use field guards and track field types")                                  \
  C(use_osr, false, true, bool, true, "Use OSR")                               \
  P(use_strong_mode_types, bool, true, "Optimize based on strong mode types.") \
  R(verbose_gc, false, bool, false, "Enables verbose GC.")                     \
  R(verbose_gc_hdr, 40, int, 40, "Print verbose GC header interval.")          \
  R(verify_after_gc, false, bool, false,                                       \
    "Enables heap verification after GC.")                                     \
  R(verify_before_gc, false, bool, false,                                      \
    "Enables heap verification before GC.")                                    \
  D(verify_gc_contains, bool, false,                                           \
    "Enables verification of address contains during GC.")                     \
  D(verify_on_transition, bool, false, "Verify on dart <==> VM.")              \
  P(enable_slow_path_sharing, bool, true, "Enable sharing of slow-path code.") \
  P(shared_slow_path_triggers_gc, bool, false,                                 \
    "TESTING: slow-path triggers a GC.")

#endif  // RUNTIME_VM_FLAG_LIST_H_
