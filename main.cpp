//
//  main.cpp
//  GraphCrawler
//
//  Created by Erik Villanueva Gomez on 9/22/25.
//

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <chrono>
#include <curl/curl.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::vector<std::string> getNeighbors(const std::string& node){
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    std::vector<std::string> neighbors;
    
    curl = curl_easy_init();
    if(curl){
        std::string url = "http://hollywood-graph-crawler.bridgesuncc.org/neighbors/" + node;
        
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        res = curl_easy_perform(curl);
        
        if(res != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        
        curl_easy_cleanup(curl);
        
        rapidjson::Document doc;
        doc.Parse(readBuffer.c_str());
        
        if(doc.HasMember("neighbors") && doc["neighbors"].IsArray()){
            for(const auto& neighbor : doc["neighbors"].GetArray()){
                neighbors.push_back(neighbor.GetString());
            }
        }
    }
    return neighbors;
}

int main(int argc, char **argv){
    if(argc != 3){
        std::cerr <<"Usage: " << argv[0] << " <start_node> <depth>" << std::endl;
        std::cerr << "Example: " << argv[0] << " \"Tom Hanks\" 2" << std::endl;
        return 1;
        
    }
    
    std::string startNode = argv[1];
    int maxDepth = std::stoi(argv[2]);
    
    std::cout << "Starting BFS from node '" << startNode << "' with depth " << maxDepth << "..." << std::endl;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    std::queue<std::string> q;
    std::unordered_set<std::string> visited;
    std::unordered_map<std::string, int> distance;
    std::vector<std::string> result_nodes;
    
    q.push(startNode);
    visited.insert(startNode);
    distance[startNode] = 0;
    
    while(!q.empty()){
        std::string currentNode = q.front();
        q.pop();
        
        result_nodes.push_back(currentNode);
        
        int currentDist = distance[currentNode];
        if(currentDist >= maxDepth){
            continue;
        }
        
        std::vector<std::string> neighbors = getNeighbors(currentNode);
        for(const auto& neighbor : neighbors){
            if(visited.find(neighbor) == visited.end()){
                visited.insert(neighbor);
                distance[neighbor] = currentDist + 1;
                q.push(neighbor);
            }
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    
    std::cout << "\n--- Visited Nodes ---" << std::endl;
    for(const auto& node : result_nodes){
        std::cout << node << " (depth: " << distance[node] << ")" << std::endl;
    }
    
    std::cout << "\nFound " << result_nodes.size() << " nodes." << std::endl;
    std::cout << "Execution time: " << elapsed.count() << " seconds." << std::endl;
    
    return 0;
}
