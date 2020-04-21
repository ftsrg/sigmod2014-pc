#include <iostream>
#include <memory>
#include "gb_utils.h"
#include "Query2.h"
#include "query-parameters.h"

std::unique_ptr<Q2Input> load(BenchmarkParameters const & parameters){
    using namespace std::chrono;
    auto load_start = high_resolution_clock::now();

    std::unique_ptr<Q2Input> input = std::make_unique<Q2Input>(parameters);

    report(parameters, 0, BenchmarkPhase::Load, round<nanoseconds>(high_resolution_clock::now() - load_start));

    return input;
}

int main(int argc, char **argv) {
    BenchmarkParameters parameters = parse_benchmark_params();
    ok(LAGraph_init());

    std::unique_ptr<Q2Input> input = load(parameters);
    
    std::vector<std::function<std::string(void)>> queriesToRun = getQueriesWithParameters(parameters, *input);

    for (auto const &task :queriesToRun) {
        task();
    }

    // Cleanup
    ok(LAGraph_finalize());

    return 0;
}