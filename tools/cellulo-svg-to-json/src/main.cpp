#include <QTextStream>
#include <QString>
#include <CelluloSVGUtil.h>

QTextStream& qPrint(){
    static QTextStream ts(stdout);
    return ts;
}

void showHelp(){
    qPrint() << "Usage: cellulo-svg-to-json [OPTIONS]\n";
    qPrint() << "    -i FILE        Name of the input SVG\n";
    qPrint() << "    -o FILE        Name of the output JSON (default is zones.json)\n";
    qPrint() << "    -d FLOAT_NUM   DPI to use when converting to millimeters (default is 90, which is the Inkscape default)\n";
    qPrint() << "    -h,--help      Shows this help\n";
}

int main(int argc, char** argv){
    float dpi = 90.0f;
    QString inputFile("");
    QString outputFile("zones.json");

    for(int i=1;i<argc;i++){
        if(QString(argv[i]) == "-i")
            inputFile = argv[i + 1];
        else if(QString(argv[i]) == "-o")
            outputFile = argv[i + 1];
        else if(QString(argv[i]) == "-d")
            dpi = QString(argv[i + 1]).toFloat();
        else if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            showHelp();
            return 0;
        }
    }

    qPrint() << "Input file: " << inputFile << "\n";
    qPrint() << "Output file: " << outputFile << "\n";
    qPrint() << "DPI: " << dpi << "\n";

    QString returnMessage = CelluloSVGUtil::dumpAllPathsToJSON(inputFile, outputFile, dpi);
    qPrint() << returnMessage.toLatin1().constData() << "\n";
    return 0;
}
