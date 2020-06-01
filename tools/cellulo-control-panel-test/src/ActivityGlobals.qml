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

    // whether the session began (very important for synchronizing cellulo with frog)
    property var sessionBegan: false

    // the activities from frog:
    property var allActivities: []

    // the elapsed time in s of the activity (used to adjust color of robot and is reset inside the next/preActivity function)
    property var elapsedActivityTime: 0

    // the total time in s of the activity (used to adjust color of robot and is reset inside the next/preActivity function) --init'ed to 1 to avoid divide by zero
    property var totalActivityTime: 1

    // individual students' progress (maps student display name to progress)
    property var studentIndivProgress: {'':0}

    // number of students
    property var numStudents: 1

    // color of leds (blue means close to zero elapsed time, violet some time has passed, red means almost no time left)
    property var colorEncodedTime: "#FF0000FF"

}
