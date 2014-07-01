//
//  CKiiQuery.h
//  cocos2dx-cpp-IFV3
//
//  Created by 熊野 聡 on 2014/06/06.
//
//

#ifndef __cocos2dx_cpp_IFV3__CKiiQuery__
#define __cocos2dx_cpp_IFV3__CKiiQuery__

#include <iostream>
#include "picojson.h"
#include "CKiiClause.h"

namespace kiicloud {

// Represents query for bucket.
class CKiiQuery
{
public:
    //! Construct query.
    //! @param clause condition applyied to this query.
    //! @param bestEffortLimit limiting maxmum number of results in the response.
    //! Actual number in the response could be smaller than
    //! specified regardress of number of remaining items in the query.
    explicit CKiiQuery(const CKiiClause& clause = CKiiClause(), const int bestEffortLimit = 0);

    //! For internal use.
    explicit CKiiQuery(const CKiiQuery &query, const std::string &paginationKey);

    //! Set sort key
    void sortByASC(const std::string& sortKey);

    //! Set sort key
    void sortByDSC(const std::string& sortKey);

    //! Serialize this query into the JSON string.
    std::string toString() const;
private:
    picojson::object jsonQuery;
};

}
#endif /* defined(__cocos2dx_cpp_IFV3__CKiiQuery__) */
