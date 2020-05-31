pragma Singleton
import QtQuick 2.0

// stores global variables relevant to the activity/orchestration
QtObject {
    // the current activity (1-indexed)
    property var currentAct: 0

    // the number of activities
    property var cntActivities: 1

    // whether the session finished
    property var sessionClosed: false

    // whether the session finished
    property var sessionBegan: false

    // the students needing help
    property var studentsStuck: [ ]

    // the activities from frog:
    property var allActivities: []
}
