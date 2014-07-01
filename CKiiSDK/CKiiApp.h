//
//  CKiiApp.h
//  cocos2dx-cpp-IFV3
//
//  Created by 熊野 聡 on 2014/06/05.
//
//

#ifndef __cocos2dx_cpp_IFV3__CKiiApp__
#define __cocos2dx_cpp_IFV3__CKiiApp__

#include <iostream>

namespace kiicloud {

//! Represents application site in KiiCloud
//! Choose one you've specified when you create your application on the developer console.
enum CKiiSite {
    cKiiSiteJP,
    cKiiSiteUS,
    cKiiSiteCN,
    cKiiSiteSG
};

//! Get base URL corresponding to site.
static std::string getBaseUrl(const CKiiSite& appSite)
{
    switch(appSite)
    {
        case kiicloud::cKiiSiteCN:
            return "https://api-cn2.kii.com/api";
        case kiicloud::cKiiSiteJP:
            return "https://api-jp.kii.com/api";
        case kiicloud::cKiiSiteUS:
            return "https://api.kii.com/api";
        case kiicloud::cKiiSiteSG:
            return "https://api-sg.kii.com/api";
    }
}

//! Represents application in KiiCloud.
struct CKiiApp
{

public:
    //! Copy constructor
    CKiiApp(const CKiiApp& rhs)
    {
        this->appId = std::string(rhs.appId);
        this->appKey = std::string(rhs.appKey);
        this->appSite = rhs.appSite;
    }

    //! Move constructor
    CKiiApp(CKiiApp&& rhs)
    {
        this->appId = std::string(rhs.appId);
        rhs.appId = "";
        this->appKey = std::string(rhs.appKey);
        rhs.appKey = "";
        this->appSite = rhs.appSite;
        rhs.appSite = cKiiSiteJP;
    }

    //! Construct app
    explicit CKiiApp(const std::string& appId, const std::string& appKey, const kiicloud::CKiiSite& appSite)
    {
        this->appId = std::string(appId);
        this->appKey = std::string(appKey);
        this->appSite = appSite;
    }

    //! Get url of app.
    std::string appUrl() const {
        std::string baseUrl = getBaseUrl(this->appSite);
        return baseUrl + "/apps/" + this->appId;
    }

    std::string appId;
    std::string appKey;
    kiicloud::CKiiSite appSite;
};

}
#endif /* defined(__cocos2dx_cpp_IFV3__CKiiApp__) */
