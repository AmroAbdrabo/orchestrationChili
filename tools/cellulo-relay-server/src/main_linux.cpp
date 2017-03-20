#include <sys/types.h>
#include <sys/stat.h>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <cerrno>
#include <unistd.h>
#include <syslog.h>

void run(){
    while(true){
        syslog(LOG_INFO, "CELLULO DAEMON !!!!! RUNNING");

        sleep(1);
    }
}

int main(int argc, char *argv[]){

    //Fork off and die
    pid_t pid = fork();
    if(pid < 0)
        exit(EXIT_FAILURE);
    if(pid > 0)
        exit(EXIT_SUCCESS);

    //pid == 0 in the child, i.e the daemon

    openlog("cellulorelayserverd", LOG_CONS | LOG_NDELAY | LOG_PID, LOG_USER);
    syslog(LOG_INFO, "Entering Daemon");

    //Files created have 666 permissions
    umask(S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

    pid_t sid = setsid();
    if(sid < 0)
        exit(EXIT_FAILURE);
    if((chdir("/")) < 0)
        exit(EXIT_FAILURE);

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    run();

    closelog();

    //QLoggingCategory::setFilterRules(QStringLiteral("qt.bluetooth* = true"));

    //QGuiApplication app(argc, argv);

    //QQmlApplicationEngine engine;

    //engine.load(QUrl(QStringLiteral("qrc:///src/main.qml")));

//    return app.exec();
//
    return 0;
}
