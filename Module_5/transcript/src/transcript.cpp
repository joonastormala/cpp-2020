#include "transcript.hpp"
#include <list>
#include <string>
#include <algorithm>

using namespace std;

void TranscriptRegistry::Add(const Transcript &t){
    data_.push_back(t);
}

void TranscriptRegistry::RemoveById(const string &id){
    data_.erase(remove_if(data_.begin(), data_.end(),
        [&] (const Transcript ref) -> bool {
            return ref.student_id==id;
        }
    ), data_.end());
}

list<Transcript>::const_iterator TranscriptRegistry::FindTranscript(const string &id) const{
    for(auto it = data_.begin(); it != data_.end(); it++){
        if(id==it->student_id) return it;
    }
    return data_.end();
}

list<pair<string, size_t>> TranscriptRegistry::FindCourseResults(const string &course) const{
    list<pair<string, size_t>> ret;
    for(auto i : data_){
        for(auto j : i.grades){
            if(j.first == course){
                pair<string, size_t> student = { i.student_id, j.second };
                ret.push_back(student);
            }
        }
    }
    return ret;
}

const list<Transcript>& TranscriptRegistry::GetTranscripts(){
    return data_;
}
