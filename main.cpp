/*
*
* Copyright 2017 Tino Melvan
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*/

#include <string>

#include "Clock\Clock.h"
#include "Converter\Reader.h"
#include "Converter\Writer.h"
#include "InputParser\InputParser.h"

void PrintUsageMessage(void) {
    printf("\nOptions:\n");
    printf("  -i [ --infile ] arg\tName of file to convert\n");
    printf("  -o [ --outfile ] arg\tName of file generated after conversion\n");
    printf("  --precision arg\t");
    printf("Real number that defines line deflection of model\n");
    printf("\t\t\tduring conversion (smaller number will result in better\n");
    printf("\t\t\tresolution of final model)\n");
    printf("  -m\t\t\tCombine shape with its YOZ mirror\n");
    printf(" - h[--help]\t\tPrint help(usage) messages\n");
}

double StringToDouble(const std::string& strPrecision) {
    double precision = atof(strPrecision.c_str());
    if (precision <= 0) {
        printf("\nWrong input of precision!\n");
        exit(EXIT_FAILURE);
    }

    return precision;
}

int main(int argc, char* argv[])
{
    Clock clock;
    Writer writer;
    InputParser inParser(argc, argv);

    if (inParser.CommandOptionExists("-h") ||
        inParser.CommandOptionExists("--help")) {
        if (argc > 2) {
            printf("\nWarning: only handling help message!\n");
        }

        atexit(PrintUsageMessage);
        return EXIT_SUCCESS;
    }

    std::string inFile = std::string();
    if (inParser.CommandOptionExists("-i")) {
        inFile = inParser.GetCommandOption("-i");
    } else if (inParser.CommandOptionExists("--infile")) {
        inFile = inParser.GetCommandOption("--infile");
    } else {
        printf("\nInput file name not detected!\n");
        return EXIT_FAILURE;
    }

    std::string outFile = std::string();
    if (inParser.CommandOptionExists("-o")) {
        outFile = inParser.GetCommandOption("-o");
    } else if (inParser.CommandOptionExists("--outfile")) {
        outFile = inParser.GetCommandOption("--outfile");
    } else {
        printf("\Output file name not detected!\n");
        return EXIT_FAILURE;
    }

    if (inParser.CommandOptionExists("--precision")) {
        std::string precision = inParser.GetCommandOption("--precision");
        writer.SetPrecision(StringToDouble(precision));
    }

    if (inParser.CommandOptionExists("-m")) {
        writer.UseMirror();
    }

    if (!inParser.UsedAllCommands()) {
        printf("\nUnknown commands present! Aborting..\n");
        return EXIT_FAILURE;
    }

    printf("[Clock] Finished parsing commands after %lf sec\n",
           clock.ElapsedSeconds());

    printf("[Converter] Staring...\n");

    Reader reader;
    if (reader.ReadFile(inFile) != IFSelect_RetDone) {
        printf("[Converter] Error during file reading\n");
        return EXIT_FAILURE;
    }

    printf("[Converter] File loaded, writting started\n");

    writer.SetShape(reader.GetShape());
    if (writer.WriteToFile(outFile) != StlAPI_StatusOK) {
        printf("[Converter] Error while writting a file\n");
        return EXIT_FAILURE;
    }

    printf("[Converter] Writting done!\n");
    printf("[Clock] Conversion lasted %lf sec\n",
           clock.ElapsedSeconds());

    return EXIT_SUCCESS;
}
