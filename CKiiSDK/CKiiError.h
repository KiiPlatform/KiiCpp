//
//  CKiiError.h
//  cocos2dx-cpp-IFV3
//
//  Created by 熊野 聡 on 2014/05/22.
//
//

#ifndef __cocos2dx_cpp_IFV3__CKiiError__
#define __cocos2dx_cpp_IFV3__CKiiError__

#include <iostream>
#include <future>

namespace kiicloud
{

class CKiiError;
typedef std::shared_ptr<CKiiError> ErrorPtr;
typedef std::future<ErrorPtr> ErrorFuture;

//! Represents error happened when accessing KiiCloud
class CKiiError
{
public:
    //! for internal use.
    explicit CKiiError();
    //! for internal use.
    explicit CKiiError(int httpErrorCode, const std::string &kiiErrorCode);
    //! copy constructor.
    explicit CKiiError(const CKiiError& rhs);
    //! move constructor.
    explicit CKiiError(CKiiError&& rhs);

    //! get HTTP error code of KiiCloud REST API.
    //! if 0, connection error happened.
    int getHttpErrorCode();

    //! get Kii error code defined by KiiCloud REST API.
    std::string getKiiErrorCode();
    
    //! Human readable string representation of this error.
    std::string toString();
private:
    int httpErrorCode;
    std::string kiiErrorCode;
};

}
#endif /* defined(__cocos2dx_cpp_IFV3__CKiiError__) */
