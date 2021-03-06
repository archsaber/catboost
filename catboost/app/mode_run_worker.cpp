#include "modes.h"
#include "bind_options.h"
#include "cmd_line.h"

#include <catboost/libs/distributed/worker.h>

#include <library/getopt/small/last_getopt.h>

#include <util/system/fs.h>
#include <util/string/iterator.h>


using namespace NCB;


namespace {
    struct TWorkerParams {
        ui32 NodePort = 0;
        ui32 ThreadCount = NSystemInfo::CachedNumberOfCpus();

        void BindParserOpts(NLastGetopt::TOpts& parser) {
            parser.AddLongOption('T', "thread-count", "worker thread count (default: core count)")
                .StoreResult(&ThreadCount);
            parser.AddLongOption("node-port", "TCP port for this worker; default is 0")
                .StoreResult(&NodePort);
        }
    };
} // anonymous namespace

int mode_run_worker(int argc, const char* argv[]) {
    TWorkerParams params;

    auto parser = NLastGetopt::TOpts();
    parser.AddHelpOption();
    params.BindParserOpts(parser);
    parser.SetFreeArgsNum(0);
    NLastGetopt::TOptsParseResult parserResult{&parser, argc, argv};

    RunWorker(params.ThreadCount, params.NodePort);

    return 0;
}
