
#include "user_object.h"

namespace gcheck {
    
UserObject::UserObject(std::vector<UserObject> cont) {
    as_string_ = "[";
    for(auto it = cont.begin(); it != cont.end();) {
        as_string_ += it->as_string_;
        if(++it != cont.end()) {
            as_string_ += ",";
        } else {
            break;
        }
    }
    as_string_ += "]";
    as_json_ = toJSON(cont);
}

UserObject MakeUserObject(const char* v) {
    return UserObject(std::string(v));
}

UserObject MakeUserObject(const UserObject& v) {
    return v;
}

UserObject MakeUserObject(const std::vector<UserObject>& v) {
    return UserObject(v);
}

void AddToUserObjectList(std::vector<UserObject>& container, const std::string& str) {
    container.push_back(MakeUserObject(str));
}

} // gcheck