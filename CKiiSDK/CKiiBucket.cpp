//
//  CKiiBucket.cpp
//  cocos2dx-cpp-IFV3
//
//  Created by 熊野 聡 on 2014/06/06.
//
//

#include "CKiiBucket.h"
#include "_CKiiGlobal.h"
#include <thread>

using kiicloud::ObjectsAndError;
using kiicloud::QueryFuture;
using kiicloud::QueryHandlerPtr;

QueryHandlerPtr kiicloud::CKiiBucket::query(
                                 const CKiiApp &app,
                                 const std::string &scopeUri,
                                 const std::string &bucketName,
                                 const CKiiQuery &query,
                                 const std::string accessToken)
{
    CKiiQueryHandler* qh = new CKiiQueryHandler(app, scopeUri, bucketName, query, accessToken);
    return QueryHandlerPtr(qh);
}

kiicloud::CKiiQueryHandler::CKiiQueryHandler(
                       const CKiiApp &app,
                       const std::string &scopeUri,
                       const std::string &bucketName,
                       const CKiiQuery &query,
                       const std::string accessToken)
:app (CKiiApp(app.appId, app.appKey, app.appSite)),
scopeUri (scopeUri),
bucketName(bucketName),
query(query),
accessToken(accessToken),
_hasNext (true)
{
}

kiicloud::CKiiQueryHandler::CKiiQueryHandler(const CKiiQueryHandler& rhs)
:app (CKiiApp(rhs.app.appId, rhs.app.appKey, rhs.app.appSite)),
scopeUri(rhs.scopeUri),
bucketName(rhs.bucketName),
query(rhs.query),
accessToken(rhs.accessToken),
_hasNext(rhs._hasNext)
{
}

kiicloud::CKiiQueryHandler::CKiiQueryHandler(CKiiQueryHandler&& rhs)
:app (CKiiApp(rhs.app.appId, rhs.app.appKey, rhs.app.appSite)),
scopeUri(rhs.scopeUri),
bucketName(rhs.bucketName),
query(rhs.query),
accessToken(rhs.accessToken),
_hasNext(rhs._hasNext)
{
    rhs.scopeUri = "";
    rhs.bucketName = "";
    rhs.query = CKiiQuery();
    rhs.accessToken = "";
    rhs._hasNext = false;
}

QueryFuture kiicloud::CKiiQueryHandler::nextPage()
{
    std::promise<ObjectsAndError> *prm = new std::promise<ObjectsAndError>();
    std::thread th1 = std::thread([=](){
        _bind->queryBucket(this->app,
                           this->scopeUri,
                           this->bucketName,
                           this->query,
                           this->accessToken,
                           [=] (picojson::value jresult, CKiiError* error)
                           {
                               ObjectsAndError pair;
                               for (int i=0; i < 1; ++i) { // dummy loop
                                   std::vector<CKiiObject> objects;
                                   if (error != nullptr) {
                                       pair = ObjectsAndError(objects, ErrorPtr(error));
                                       break;
                                   }
                                   picojson::object resObj = jresult.get<picojson::object>();
                                   // parse next.
                                   this->_hasNext = false;
                                   if (resObj["nextPaginationKey"].is<std::string>()) {
                                       std::string nPKey = resObj["nextPaginationKey"].get<std::string>();
                                       if (!nPKey.empty()) {
                                           this->_hasNext = true;
                                           this->query = CKiiQuery(query, nPKey);
                                       }
                                   }
                                   
                                   picojson::array objs = resObj["results"].get<picojson::array>();
                                   std::vector<picojson::value>::iterator itr = objs.begin();
                                   while (itr != objs.end())
                                   {
                                       picojson::object aObj = (*itr).get<picojson::object>();
                                       CKiiObject kobj = CKiiObject(this->scopeUri, this->bucketName, aObj);
                                       objects.push_back(kobj);
                                       ++itr;
                                   }
                                   pair = ObjectsAndError(objects, ErrorPtr(error));
                                   break;
                               }
                               prm->set_value(pair);
                               delete  prm;
                           });
    });
    th1.detach();
    return prm->get_future();
}

bool kiicloud::CKiiQueryHandler::hasNext()
{
    return this->_hasNext;
}
