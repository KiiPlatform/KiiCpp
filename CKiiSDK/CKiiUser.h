//
//  CKiiUser.h
//  cocos2dx-cpp-IFV3
//
//  Created by 熊野 聡 on 2014/05/23.
//
//

#ifndef __cocos2dx_cpp_IFV3__CKiiUser__
#define __cocos2dx_cpp_IFV3__CKiiUser__

#include <iostream>
#include <future>
#include "CKiiApp.h"
#include "CKiiError.h"
#include "picojson.h"

using kiicloud::ErrorPtr;
using kiicloud::ErrorFuture;

namespace kiicloud {
class CKiiUser;
typedef std::shared_ptr<CKiiUser> UserPtr;
typedef std::pair<UserPtr, ErrorPtr> UserAndError;
typedef std::future<UserAndError> UserFuture;

//! Represents User in Kii Cloud
class CKiiUser {
public:
    //! for interntal use
    explicit CKiiUser();

    //! for internal use
    explicit CKiiUser(const picojson::value& keyValues);

    //! get key values of this user.
    picojson::object getKeyValues() const;

    //! get access token of this user.
    std::string getAccessToken() const;

    //! get ID of this user.
    std::string getId() const;

    //! get URI of this user.
    std::string getUri() const;

    //! login with user name and password.
    static UserFuture login(
                            const CKiiApp& app,
                            const std::string& username,
                            const std::string& password);

    //! register new user with user name and password.
    static UserFuture registerNewUser(const CKiiApp& app,
                                      const std::string& username,
                                      const std::string& password);

    //! Refresh user. key-values of this user would be updated with
    //! latest value in KiiCloud
    static ErrorFuture refresh(const kiicloud::CKiiApp& app,
                              kiicloud::CKiiUser& user);

private:
    picojson::object keyValues;
    std::string appId;
    CKiiSite appSite;
    std::string accessToken;
    std::string userId;
};

};

#endif /* defined(__cocos2dx_cpp_IFV3__CKiiUser__) */
