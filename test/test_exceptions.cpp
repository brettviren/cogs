#include "ers/ers.h"

ERS_DECLARE_ISSUE(cogs, TestIssue,
                  "A test issue occured with value " << value,
                   ((const char*) value))

int main()
{
    cogs::TestIssue issue(ERS_HERE, "42");
    ers::warning( issue );

    try {
        throw issue;
    }
    catch (cogs::TestIssue& ti) {
        ERS_LOG("caught issue: " << ti.get_uid());
        ers::error(ti);
    }
    return 0;
}
