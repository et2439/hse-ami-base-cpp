#include "search.h"

double CalculateTF(const std::string& substring, const std::string& word) {
    size_t count = 0;
    size_t pos = substring.find(word);
    while (pos != std::string::npos) {
        ++count;
        pos = substring.find(word, pos + word.size());
    }
    size_t count_words = (std::count(substring.begin(), substring.end(), ' ')) - 1;
    return static_cast<double>(count) / static_cast<double>(count_words);
}

double CalculateIDF(const std::vector<std::string>& substrings, const std::string& word) {
    size_t count = 0;
    size_t count_words = 0;
    for (const auto& sentence : substrings) {
        ++count_words;
        if (sentence.find(word) != std::string::npos) {
            ++count;
        }
    }

    return count > 0 ? std::log(static_cast<double>(count_words) / static_cast<double>(count)) : 0.0;
}

std::tuple<std::vector<std::string>, std::vector<std::size_t>> Split(std::string_view text) {
    std::vector<std::string> result;
    size_t start = 0;
    size_t end = text.find('\n');
    std::vector<std::size_t> starts_ends;
    while (end != std::string::npos || start < text.size() - 1) {
        std::string str_tmp = " ";
        if (end == std::string::npos) {
            end = text.size();
        }
        for (size_t i = start; i < end; ++i) {
            if (std::isalpha(text[i])) {
                str_tmp += static_cast<char>(std::tolower(text[i]));
            } else if (!str_tmp.empty() && str_tmp.back() != ' ') {
                str_tmp += " ";
            }
        }
        str_tmp += " ";
        result.push_back(str_tmp);
        starts_ends.push_back(start);
        start = end + 1;
        end = text.find('\n', start);
    }
    if (text[text.size() - 1] == '\n') {
        starts_ends.push_back(text.size());
    } else {
        starts_ends.push_back(text.size() + 1);
    }

    return std::make_tuple(result, starts_ends);
}

bool CompSentencesIndex(const std::tuple<size_t, double>& sent1, const std::tuple<size_t, double>& sent2) {
    size_t tf_idf_1 = std::get<0>(sent1);
    size_t tf_idf_2 = std::get<0>(sent2);
    return tf_idf_1 < tf_idf_2;
}

bool CompSentences(const std::tuple<size_t, double>& sent1, const std::tuple<size_t, double>& sent2) {
    double tf_idf_1 = std::get<1>(sent1);
    double tf_idf_2 = std::get<1>(sent2);
    return tf_idf_1 > tf_idf_2;
}

std::vector<std::string_view> Search(std::string_view text, std::string_view query, size_t results_count) {
    std::vector<std::string_view> result;
    std::tuple<std::vector<std::string>, std::vector<std::size_t>> tmp_tuple = Split(text);
    std::vector<std::string>& substrings = std::get<0>(tmp_tuple);
    std::vector<std::size_t>& starts_ends = std::get<1>(tmp_tuple);
    std::map<std::string, double> query_words;
    std::vector<std::tuple<size_t, double>> sentences_tf_idfs;
    size_t sentence_count = 0;

    size_t i = 0;
    while (i < query.size()) {
        std::string word_tmp = " ";
        while (std::isalpha(query[i])) {
            word_tmp += static_cast<char>(std::tolower(query[i]));
            ++i;
        }
        if (!word_tmp.empty()) {
            if (!query_words.contains(word_tmp)) {
                word_tmp = word_tmp + " ";
                query_words[word_tmp] = CalculateIDF(substrings, word_tmp);
            }
            word_tmp.clear();
        }
        ++i;
    }

    for (const auto& sentence : substrings) {
        double sentence_tf_idf = 0.0;
        for (const auto& word_idf_pair : query_words) {
            double tf = CalculateTF(sentence, word_idf_pair.first);
            sentence_tf_idf += tf * word_idf_pair.second;
        }
        if (sentence_tf_idf > 0) {
            sentences_tf_idfs.push_back(std::make_tuple(sentence_count, sentence_tf_idf));
        }
        ++sentence_count;
    }

    std::sort(sentences_tf_idfs.begin(), sentences_tf_idfs.end(), CompSentencesIndex);
    std::stable_sort(sentences_tf_idfs.begin(), sentences_tf_idfs.end(), CompSentences);

    for (size_t i = 0; i < std::min(results_count, sentences_tf_idfs.size()); ++i) {
        size_t sentence_index = std::get<0>(sentences_tf_idfs[i]);
        if (sentence_index == starts_ends.size() - 1) {
            result.push_back(text.substr(starts_ends[sentence_index], text.size() - starts_ends[sentence_index] - 1));

        } else {
            result.push_back(text.substr(starts_ends[sentence_index],
                                         starts_ends[sentence_index + 1] - starts_ends[sentence_index] - 1));
        }
    }
    return result;
}
