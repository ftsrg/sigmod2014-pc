#include "query-parameters.h"
#include "Query2.h"

template<typename QueryType, typename... ParameterT>
auto getQueryWrapper(BenchmarkParameters benchmark_parameters, Q2Input const &input) {
    return [=, &input](ParameterT &&...query_parameters, std::string expected_result) -> std::function<std::string()> {
        return [=, &input]() -> std::string {
            return QueryType(benchmark_parameters, std::make_tuple(query_parameters...), input).initial_calculation();
        };
    };
}

//std::function<std::string()> query2(int top_k_limit, std::string birtday_limit_str) {
//    return [top_k_limit, &birtday_limit_str](BenchmarkParameters const &benchmark_parameters) {
//        return Query2(benchmarkParameters, std::make_tuple(top_k_limit, birtday_limit_str)).initial_calculation();
//    };
//}

std::vector<std::function<std::string()>>
getQueriesWithParameters(BenchmarkParameters benchmark_parameters, Q2Input const &input) {
    auto query2 = getQueryWrapper<Query2, int, std::string>(benchmark_parameters, input);

    std::vector<std::function<std::string()>> vector{
//            query2(3, "1980-02-01", "Chiang_Kai-shek Augustine_of_Hippo Napoleon % component sizes 22 16 16"),
//            query2(4, "1981-03-10", "Chiang_Kai-shek Napoleon Mohandas_Karamchand_Gandhi Sukarno % component sizes 17 13 11 11"),
//            query2(3, "1982-03-29", "Chiang_Kai-shek Mohandas_Karamchand_Gandhi Napoleon % component sizes 13 11 10"),
//            query2(3, "1983-05-09", "Chiang_Kai-shek Mohandas_Karamchand_Gandhi Augustine_of_Hippo % component sizes 12 10 8"),
//            query2(5, "1984-07-02", "Chiang_Kai-shek Aristotle Mohandas_Karamchand_Gandhi Augustine_of_Hippo Fidel_Castro % component sizes 10 7 6 5 5"),
//            query2(3, "1985-05-31", "Chiang_Kai-shek Mohandas_Karamchand_Gandhi Joseph_Stalin % component sizes 6 6 5"),
            query2(3, "1986-06-14", "Chiang_Kai-shek Mohandas_Karamchand_Gandhi Joseph_Stalin % component sizes 6 6 5"),
//            query2(7, "1987-06-24", "Chiang_Kai-shek Augustine_of_Hippo Genghis_Khan Haile_Selassie_I Karl_Marx Lyndon_B._Johnson Robert_John_\"Mutt\"_Lange % component sizes 4 3 3 3 3 3 3"),
    };

    return vector;
}