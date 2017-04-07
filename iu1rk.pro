#-------------------------------------------------
#
# Project created by QtCreator 2016-05-04T17:55:15
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = chuaviz
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot/qcustomplot.cpp \
    Point3DT.cpp \
    TrajectoryCalculator.cpp \
    Trajectory.cpp \
    widgets/trajectorywidget.cpp \
    circuitparameters.cpp \
    widgets/crosssectionwidget.cpp \
    widgets/testinputwidget.cpp \
    trajectorytest.cpp \
    trajectoryresult.cpp \
    crosssectionmap.cpp \
    widgets/squarelayout.cpp \
    widgets/circuitparameterswidget.cpp \
    widgets/csseriewidget.cpp \
    qplot3d/QPlot3D.cpp \
    widgets/customspinbox.cpp \
    utils.cpp \
    widgets/customdoublespinbox.cpp \
    calculatedcrosssection.cpp \
    partiallycalculatedcrosssection.cpp

HEADERS  += mainwindow.h \
    qcustomplot/qcustomplot.h \
    Point3DT.h \
    TrajectoryCalculator.h \
    Trajectory.h \
    widgets/trajectorywidget.h \
    circuitparameters.h \
    crosssectiontype.h \
    tbb/include/serial/tbb/parallel_for.h \
    tbb/include/serial/tbb/tbb_annotate.h \
    tbb/include/tbb/compat/condition_variable \
    tbb/include/tbb/compat/ppl.h \
    tbb/include/tbb/compat/thread \
    tbb/include/tbb/compat/tuple \
    tbb/include/tbb/internal/_aggregator_impl.h \
    tbb/include/tbb/internal/_concurrent_queue_impl.h \
    tbb/include/tbb/internal/_concurrent_unordered_impl.h \
    tbb/include/tbb/internal/_flow_graph_async_msg_impl.h \
    tbb/include/tbb/internal/_flow_graph_impl.h \
    tbb/include/tbb/internal/_flow_graph_indexer_impl.h \
    tbb/include/tbb/internal/_flow_graph_item_buffer_impl.h \
    tbb/include/tbb/internal/_flow_graph_join_impl.h \
    tbb/include/tbb/internal/_flow_graph_node_impl.h \
    tbb/include/tbb/internal/_flow_graph_streaming_node.h \
    tbb/include/tbb/internal/_flow_graph_tagged_buffer_impl.h \
    tbb/include/tbb/internal/_flow_graph_trace_impl.h \
    tbb/include/tbb/internal/_flow_graph_types_impl.h \
    tbb/include/tbb/internal/_mutex_padding.h \
    tbb/include/tbb/internal/_range_iterator.h \
    tbb/include/tbb/internal/_tbb_hash_compare_impl.h \
    tbb/include/tbb/internal/_tbb_strings.h \
    tbb/include/tbb/internal/_tbb_windef.h \
    tbb/include/tbb/internal/_template_helpers.h \
    tbb/include/tbb/internal/_x86_eliding_mutex_impl.h \
    tbb/include/tbb/internal/_x86_rtm_rw_mutex_impl.h \
    tbb/include/tbb/machine/gcc_armv7.h \
    tbb/include/tbb/machine/gcc_generic.h \
    tbb/include/tbb/machine/gcc_ia32_common.h \
    tbb/include/tbb/machine/gcc_itsx.h \
    tbb/include/tbb/machine/ibm_aix51.h \
    tbb/include/tbb/machine/icc_generic.h \
    tbb/include/tbb/machine/linux_common.h \
    tbb/include/tbb/machine/linux_ia32.h \
    tbb/include/tbb/machine/linux_ia64.h \
    tbb/include/tbb/machine/linux_intel64.h \
    tbb/include/tbb/machine/mac_ppc.h \
    tbb/include/tbb/machine/macos_common.h \
    tbb/include/tbb/machine/mic_common.h \
    tbb/include/tbb/machine/msvc_armv7.h \
    tbb/include/tbb/machine/msvc_ia32_common.h \
    tbb/include/tbb/machine/sunos_sparc.h \
    tbb/include/tbb/machine/windows_api.h \
    tbb/include/tbb/machine/windows_ia32.h \
    tbb/include/tbb/machine/windows_intel64.h \
    tbb/include/tbb/machine/xbox360_ppc.h \
    tbb/include/tbb/aggregator.h \
    tbb/include/tbb/aligned_space.h \
    tbb/include/tbb/atomic.h \
    tbb/include/tbb/blocked_range.h \
    tbb/include/tbb/blocked_range2d.h \
    tbb/include/tbb/blocked_range3d.h \
    tbb/include/tbb/cache_aligned_allocator.h \
    tbb/include/tbb/combinable.h \
    tbb/include/tbb/concurrent_hash_map.h \
    tbb/include/tbb/concurrent_lru_cache.h \
    tbb/include/tbb/concurrent_priority_queue.h \
    tbb/include/tbb/concurrent_queue.h \
    tbb/include/tbb/concurrent_unordered_map.h \
    tbb/include/tbb/concurrent_unordered_set.h \
    tbb/include/tbb/concurrent_vector.h \
    tbb/include/tbb/critical_section.h \
    tbb/include/tbb/enumerable_thread_specific.h \
    tbb/include/tbb/flow_graph.h \
    tbb/include/tbb/flow_graph_abstractions.h \
    tbb/include/tbb/flow_graph_opencl_node.h \
    tbb/include/tbb/global_control.h \
    tbb/include/tbb/memory_pool.h \
    tbb/include/tbb/mutex.h \
    tbb/include/tbb/null_mutex.h \
    tbb/include/tbb/null_rw_mutex.h \
    tbb/include/tbb/parallel_do.h \
    tbb/include/tbb/parallel_for.h \
    tbb/include/tbb/parallel_for_each.h \
    tbb/include/tbb/parallel_invoke.h \
    tbb/include/tbb/parallel_reduce.h \
    tbb/include/tbb/parallel_scan.h \
    tbb/include/tbb/parallel_sort.h \
    tbb/include/tbb/parallel_while.h \
    tbb/include/tbb/partitioner.h \
    tbb/include/tbb/pipeline.h \
    tbb/include/tbb/queuing_mutex.h \
    tbb/include/tbb/queuing_rw_mutex.h \
    tbb/include/tbb/reader_writer_lock.h \
    tbb/include/tbb/recursive_mutex.h \
    tbb/include/tbb/runtime_loader.h \
    tbb/include/tbb/scalable_allocator.h \
    tbb/include/tbb/spin_mutex.h \
    tbb/include/tbb/spin_rw_mutex.h \
    tbb/include/tbb/task.h \
    tbb/include/tbb/task_arena.h \
    tbb/include/tbb/task_group.h \
    tbb/include/tbb/task_scheduler_init.h \
    tbb/include/tbb/task_scheduler_observer.h \
    tbb/include/tbb/tbb.h \
    tbb/include/tbb/tbb_allocator.h \
    tbb/include/tbb/tbb_config.h \
    tbb/include/tbb/tbb_exception.h \
    tbb/include/tbb/tbb_machine.h \
    tbb/include/tbb/tbb_profiling.h \
    tbb/include/tbb/tbb_stddef.h \
    tbb/include/tbb/tbb_thread.h \
    tbb/include/tbb/tbbmalloc_proxy.h \
    tbb/include/tbb/tick_count.h \
    trajectoryresult.h \
    widgets/crosssectionwidget.h \
    widgets/testinputwidget.h \
    trajectorytest.h \
    trajectoryresulttype.h \
    crosssectionmap.h \
    widgets/squarelayout.h \
    widgets/circuitparameterswidget.h \
    widgets/csseriewidget.h \
    qplot3d/QPlot3D.h \
    widgets/customspinbox.h \
    utils.h \
    widgets/customdoublespinbox.h \
    calculatedcrosssection.h \
    partiallycalculatedcrosssection.h \
    vacharacteristic.h

FORMS    += mainwindow.ui \
    widgets/trajectorywidget.ui \
    widgets/crosssectionwidget.ui \
    widgets/testinputwidget.ui \
    widgets/circuitparameterswidget.ui \
    widgets/csseriewidget.ui

DISTFILES += \
    parameters.txt \
    tbb/bin/ia32/vc11/tbb.pdb \
    tbb/bin/ia32/vc11/tbb_debug.pdb \
    tbb/bin/ia32/vc11/tbb_preview.pdb \
    tbb/bin/ia32/vc11/tbb_preview_debug.pdb \
    tbb/bin/ia32/vc11/tbbmalloc.pdb \
    tbb/bin/ia32/vc11/tbbmalloc_debug.pdb \
    tbb/bin/ia32/vc11/tbbmalloc_proxy.pdb \
    tbb/bin/ia32/vc11/tbbmalloc_proxy_debug.pdb \
    tbb/bin/ia32/vc12/tbb.pdb \
    tbb/bin/ia32/vc12/tbb_debug.pdb \
    tbb/bin/ia32/vc12/tbb_preview.pdb \
    tbb/bin/ia32/vc12/tbb_preview_debug.pdb \
    tbb/bin/ia32/vc12/tbbmalloc.pdb \
    tbb/bin/ia32/vc12/tbbmalloc_debug.pdb \
    tbb/bin/ia32/vc12/tbbmalloc_proxy.pdb \
    tbb/bin/ia32/vc12/tbbmalloc_proxy_debug.pdb \
    tbb/bin/intel64/vc11/tbb.pdb \
    tbb/bin/intel64/vc11/tbb_debug.pdb \
    tbb/bin/intel64/vc11/tbb_preview.pdb \
    tbb/bin/intel64/vc11/tbb_preview_debug.pdb \
    tbb/bin/intel64/vc11/tbbmalloc.pdb \
    tbb/bin/intel64/vc11/tbbmalloc_debug.pdb \
    tbb/bin/intel64/vc11/tbbmalloc_proxy.pdb \
    tbb/bin/intel64/vc11/tbbmalloc_proxy_debug.pdb \
    tbb/bin/intel64/vc12/tbb.pdb \
    tbb/bin/intel64/vc12/tbb_debug.pdb \
    tbb/bin/intel64/vc12/tbb_preview.pdb \
    tbb/bin/intel64/vc12/tbb_preview_debug.pdb \
    tbb/bin/intel64/vc12/tbbmalloc.pdb \
    tbb/bin/intel64/vc12/tbbmalloc_debug.pdb \
    tbb/bin/intel64/vc12/tbbmalloc_proxy.pdb \
    tbb/bin/intel64/vc12/tbbmalloc_proxy_debug.pdb \
    tbb/lib/ia32/vc11/tbbproxy.pdb \
    tbb/lib/ia32/vc11/tbbproxy_debug.pdb \
    tbb/lib/ia32/vc12/tbbproxy.pdb \
    tbb/lib/ia32/vc12/tbbproxy_debug.pdb \
    tbb/lib/intel64/vc11/tbbproxy.pdb \
    tbb/lib/intel64/vc11/tbbproxy_debug.pdb \
    tbb/lib/intel64/vc12/tbbproxy.pdb \
    tbb/lib/intel64/vc12/tbbproxy_debug.pdb \
    tbb/lib/ia32/vc11/tbb.lib \
    tbb/lib/ia32/vc11/tbb_debug.lib \
    tbb/lib/ia32/vc11/tbb_preview.lib \
    tbb/lib/ia32/vc11/tbb_preview_debug.lib \
    tbb/lib/ia32/vc11/tbbmalloc.lib \
    tbb/lib/ia32/vc11/tbbmalloc_debug.lib \
    tbb/lib/ia32/vc11/tbbmalloc_proxy.lib \
    tbb/lib/ia32/vc11/tbbmalloc_proxy_debug.lib \
    tbb/lib/ia32/vc11/tbbproxy.lib \
    tbb/lib/ia32/vc11/tbbproxy_debug.lib \
    tbb/lib/ia32/vc12/tbb.lib \
    tbb/lib/ia32/vc12/tbb_debug.lib \
    tbb/lib/ia32/vc12/tbb_preview.lib \
    tbb/lib/ia32/vc12/tbb_preview_debug.lib \
    tbb/lib/ia32/vc12/tbbmalloc.lib \
    tbb/lib/ia32/vc12/tbbmalloc_debug.lib \
    tbb/lib/ia32/vc12/tbbmalloc_proxy.lib \
    tbb/lib/ia32/vc12/tbbmalloc_proxy_debug.lib \
    tbb/lib/ia32/vc12/tbbproxy.lib \
    tbb/lib/ia32/vc12/tbbproxy_debug.lib \
    tbb/lib/intel64/vc11/tbb.lib \
    tbb/lib/intel64/vc11/tbb_debug.lib \
    tbb/lib/intel64/vc11/tbb_preview.lib \
    tbb/lib/intel64/vc11/tbb_preview_debug.lib \
    tbb/lib/intel64/vc11/tbbmalloc.lib \
    tbb/lib/intel64/vc11/tbbmalloc_debug.lib \
    tbb/lib/intel64/vc11/tbbmalloc_proxy.lib \
    tbb/lib/intel64/vc11/tbbmalloc_proxy_debug.lib \
    tbb/lib/intel64/vc11/tbbproxy.lib \
    tbb/lib/intel64/vc11/tbbproxy_debug.lib \
    tbb/lib/intel64/vc12/tbb.lib \
    tbb/lib/intel64/vc12/tbb_debug.lib \
    tbb/lib/intel64/vc12/tbb_preview.lib \
    tbb/lib/intel64/vc12/tbb_preview_debug.lib \
    tbb/lib/intel64/vc12/tbbmalloc.lib \
    tbb/lib/intel64/vc12/tbbmalloc_debug.lib \
    tbb/lib/intel64/vc12/tbbmalloc_proxy.lib \
    tbb/lib/intel64/vc12/tbbmalloc_proxy_debug.lib \
    tbb/lib/intel64/vc12/tbbproxy.lib \
    tbb/lib/intel64/vc12/tbbproxy_debug.lib \
    tbb/bin/tbbvars.csh \
    tbb/bin/ia32/vc11/tbb.dll \
    tbb/bin/ia32/vc11/tbb_debug.dll \
    tbb/bin/ia32/vc11/tbb_preview.dll \
    tbb/bin/ia32/vc11/tbb_preview_debug.dll \
    tbb/bin/ia32/vc11/tbbmalloc.dll \
    tbb/bin/ia32/vc11/tbbmalloc_debug.dll \
    tbb/bin/ia32/vc11/tbbmalloc_proxy.dll \
    tbb/bin/ia32/vc11/tbbmalloc_proxy_debug.dll \
    tbb/bin/ia32/vc12/tbb.dll \
    tbb/bin/ia32/vc12/tbb_debug.dll \
    tbb/bin/ia32/vc12/tbb_preview.dll \
    tbb/bin/ia32/vc12/tbb_preview_debug.dll \
    tbb/bin/ia32/vc12/tbbmalloc.dll \
    tbb/bin/ia32/vc12/tbbmalloc_debug.dll \
    tbb/bin/ia32/vc12/tbbmalloc_proxy.dll \
    tbb/bin/ia32/vc12/tbbmalloc_proxy_debug.dll \
    tbb/bin/intel64/vc11/tbb.dll \
    tbb/bin/intel64/vc11/tbb_debug.dll \
    tbb/bin/intel64/vc11/tbb_preview.dll \
    tbb/bin/intel64/vc11/tbb_preview_debug.dll \
    tbb/bin/intel64/vc11/tbbmalloc.dll \
    tbb/bin/intel64/vc11/tbbmalloc_debug.dll \
    tbb/bin/intel64/vc11/tbbmalloc_proxy.dll \
    tbb/bin/intel64/vc11/tbbmalloc_proxy_debug.dll \
    tbb/bin/intel64/vc12/tbb.dll \
    tbb/bin/intel64/vc12/tbb_debug.dll \
    tbb/bin/intel64/vc12/tbb_preview.dll \
    tbb/bin/intel64/vc12/tbb_preview_debug.dll \
    tbb/bin/intel64/vc12/tbbmalloc.dll \
    tbb/bin/intel64/vc12/tbbmalloc_debug.dll \
    tbb/bin/intel64/vc12/tbbmalloc_proxy.dll \
    tbb/bin/intel64/vc12/tbbmalloc_proxy_debug.dll \
    tbb/lib/ia32/gcc4.7/libtbb.so \
    tbb/lib/ia32/gcc4.7/libtbb.so.2 \
    tbb/lib/ia32/gcc4.7/libtbb_debug.so \
    tbb/lib/ia32/gcc4.7/libtbb_debug.so.2 \
    tbb/lib/ia32/gcc4.7/libtbb_preview.so \
    tbb/lib/ia32/gcc4.7/libtbb_preview.so.2 \
    tbb/lib/ia32/gcc4.7/libtbb_preview_debug.so \
    tbb/lib/ia32/gcc4.7/libtbb_preview_debug.so.2 \
    tbb/lib/ia32/gcc4.7/libtbbmalloc.so \
    tbb/lib/ia32/gcc4.7/libtbbmalloc.so.2 \
    tbb/lib/ia32/gcc4.7/libtbbmalloc_debug.so \
    tbb/lib/ia32/gcc4.7/libtbbmalloc_debug.so.2 \
    tbb/lib/ia32/gcc4.7/libtbbmalloc_proxy.so \
    tbb/lib/ia32/gcc4.7/libtbbmalloc_proxy.so.2 \
    tbb/lib/ia32/gcc4.7/libtbbmalloc_proxy_debug.so \
    tbb/lib/ia32/gcc4.7/libtbbmalloc_proxy_debug.so.2 \
    tbb/lib/intel64/gcc4.7/libtbb.so \
    tbb/lib/intel64/gcc4.7/libtbb.so.2 \
    tbb/lib/intel64/gcc4.7/libtbb_debug.so \
    tbb/lib/intel64/gcc4.7/libtbb_debug.so.2 \
    tbb/lib/intel64/gcc4.7/libtbb_preview.so \
    tbb/lib/intel64/gcc4.7/libtbb_preview.so.2 \
    tbb/lib/intel64/gcc4.7/libtbb_preview_debug.so \
    tbb/lib/intel64/gcc4.7/libtbb_preview_debug.so.2 \
    tbb/lib/intel64/gcc4.7/libtbbmalloc.so \
    tbb/lib/intel64/gcc4.7/libtbbmalloc.so.2 \
    tbb/lib/intel64/gcc4.7/libtbbmalloc_debug.so \
    tbb/lib/intel64/gcc4.7/libtbbmalloc_debug.so.2 \
    tbb/lib/intel64/gcc4.7/libtbbmalloc_proxy.so \
    tbb/lib/intel64/gcc4.7/libtbbmalloc_proxy.so.2 \
    tbb/lib/intel64/gcc4.7/libtbbmalloc_proxy_debug.so \
    tbb/lib/intel64/gcc4.7/libtbbmalloc_proxy_debug.so.2 \
    tbb/lib/mic/libtbb.so \
    tbb/lib/mic/libtbb.so.2 \
    tbb/lib/mic/libtbb_debug.so \
    tbb/lib/mic/libtbb_debug.so.2 \
    tbb/lib/mic/libtbb_preview.so \
    tbb/lib/mic/libtbb_preview.so.2 \
    tbb/lib/mic/libtbb_preview_debug.so \
    tbb/lib/mic/libtbb_preview_debug.so.2 \
    tbb/lib/mic/libtbbmalloc.so \
    tbb/lib/mic/libtbbmalloc.so.2 \
    tbb/lib/mic/libtbbmalloc_debug.so \
    tbb/lib/mic/libtbbmalloc_debug.so.2 \
    tbb/lib/mic/libtbbmalloc_proxy.so \
    tbb/lib/mic/libtbbmalloc_proxy.so.2 \
    tbb/lib/mic/libtbbmalloc_proxy_debug.so \
    tbb/lib/mic/libtbbmalloc_proxy_debug.so.2 \
    tbb/bin/tbbvars.sh \
    tbb/include/tbb/index.html \
    tbb/include/index.html \
    tbb/index.html \
    exprtk/readme.txt \
    tbb/bin/tbbvars.bat \
    tbb/lib/ia32/vc11/tbb.def \
    tbb/lib/ia32/vc11/tbbmalloc.def \
    tbb/lib/ia32/vc12/tbb.def \
    tbb/lib/ia32/vc12/tbbmalloc.def \
    tbb/lib/intel64/vc11/tbb.def \
    tbb/lib/intel64/vc11/tbbmalloc.def \
    tbb/lib/intel64/vc12/tbb.def \
    tbb/lib/intel64/vc12/tbbmalloc.def \
    tbb/CHANGES \
    tbb/LICENSE \
    tbb/README.md \
    tbb/README \
    CHANGELOG

INCLUDEPATH += "$$PWD/tbb/include"
INCLUDEPATH += "$$PWD/exprtk"


CONFIG(debug, debug|release) {
    linux{
        LIBS += -L"$$PWD/tbb/lib/intel64/gcc4.7" -ltbb_debug

    }

    win32{
        win32:contains(QMAKE_HOST.arch, x86_64) {
            LIBS += -L"$$PWD\\tbb\\lib\\intel64\\vc12" -ltbb_debug -lopengl32d -lglu32d
        } else {
            LIBS += -L"$$PWD\\tbb\\lib\\ia32\\vc12" -ltbb_debug -lopengl32d -lglu32d
        }
        QMAKE_CXXFLAGS += -bigobj
    }
}

CONFIG(release, debug|release) {
    linux{
        LIBS += -L"$$PWD/tbb/lib/intel64/gcc4.7" -ltbb
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE += -O2
#QMAKE_CXXFLAGS_RELEASE += -O3
#QMAKE_CXXFLAGS_RELEASE += -march=haswell
#QMAKE_CXXFLAGS_RELEASE += -mavx2 -mfma
    }

    win32{
        win32:contains(QMAKE_HOST.arch, x86_64) {
            LIBS += -L"$$PWD\\tbb\\lib\\intel64\\vc12" -ltbb -lopengl32 -lglu32
        } else {
            LIBS += -L"$$PWD\\tbb\\lib\\ia32\\vc12" -ltbb -lopengl32 -lglu32
        }
        QMAKE_CXXFLAGS += -bigobj
    }
}

RESOURCES += \
    images.qrc
