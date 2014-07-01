//
//  CKiiBucket.h
//  cocos2dx-cpp-IFV3
//
//  Created by 熊野 聡 on 2014/06/06.
//
//

#ifndef __cocos2dx_cpp_IFV3__CKiiBucket__
#define __cocos2dx_cpp_IFV3__CKiiBucket__

#include <iostream>
#include <vector>
#include "CKiiObject.h"
#include "CKiiError.h"
#include "CKiiQuery.h"
#include "CKiiApp.h"

namespace kiicloud{

typedef std::pair<std::vector<CKiiObject>, ErrorPtr> ObjectsAndError;
typedef std::future<ObjectsAndError> QueryFuture;

//! Handler of bucket query.
class CKiiQueryHandler {
public:
    //! For internal use.
    explicit CKiiQueryHandler(
                          const CKiiApp &app,
                          const std::string &scopeUri,
                          const std::string &bucketName,
                          const CKiiQuery &query,
                          const std::string accessToken);

    //! Copy constructor
    CKiiQueryHandler(const CKiiQueryHandler& rhs);

    //! Move constructor
    CKiiQueryHandler(CKiiQueryHandler&& rhs);

    //! Get next page of this query
    QueryFuture nextPage();

    //! Test if query has next page
    bool hasNext();

private:
    CKiiApp app;
    std::string scopeUri;
    std::string bucketName;
    CKiiQuery query;
    std::string accessToken;
    bool _hasNext;
};

//! Represents bucket in KiiCloud
class CKiiBucket
{
public:
    //! Obtain bucket query handler.
    static CKiiQueryHandler* query(
                               const CKiiApp &app,
                               const std::string &scopeUri,
                               const std::string &bucketName,
                               const CKiiQuery &query,
                               const std::string accessToken);
};

}
#endif /* defined(__cocos2dx_cpp_IFV3__CKiiBucket__) */
