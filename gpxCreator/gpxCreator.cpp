#include "stdafx.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>

const int secondsPerSplit = 6;
const double lonGain = 0.0001;

std::string toTwoDigits(int num) {
	std::string str = std::to_string(num);
	if (str.length() == 1) {
		str.insert(0, "0");
	}
	return str;
}

std::string formatTime(int time) {
	int hours, mins, secs;
	secs = time % 60;
	time /= 60;
	mins = time % 60;
	time /= 60;
	hours = time;
	std::string colon = ":";

	return toTwoDigits(hours) + colon + toTwoDigits(mins) + colon + toTwoDigits(secs);
}

std::string getHeader() {
	std::stringstream result;
	result << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" <<
		"<gpx creator=\"StravaGPX\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" " <<
		"xsi:schemaLocation=\"http://www.topografix.com/GPX/1/1 " <<
		"http://www.topografix.com/GPX/1/1/gpx.xsd http://www.garmin.com/xmlschemas/GpxExtensions/v3 " <<
		"http://www.garmin.com/xmlschemas/GpxExtensionsv3.xsd " <<
		"http://www.garmin.com/xmlschemas/TrackPointExtension/v1 " <<
		"http://www.garmin.com/xmlschemas/TrackPointExtensionv1.xsd\" " <<
		"version=\"1.1\" xmlns=\"http://www.topografix.com/GPX/1/1\" " <<
		"xmlns:gpxtpx=\"http://www.garmin.com/xmlschemas/TrackPointExtension/v1\" " <<
		"xmlns:gpxx=\"http://www.garmin.com/xmlschemas/GpxExtensions/v3\">\n" <<
		" <metadata>\n" <<
		"  <time>2019-06-28T10:00:00Z</time>\n" <<
		" </metadata>\n" <<
		" <trk>\n" <<
		"  <name>hr test</name>\n" <<
		"  <type>9</type>\n" <<
		"  <trkseg>\n";
	return result.str();

}

std::string getTrackPoint(double lat, double lon, std::string time, int hr) {
	std::stringstream result;
	result << "   <trkpt lat=\"" << lat << "\" lon=\"" << lon << "\">\n" <<
		"    <time>2019-06-28T" << time << "Z</time>\n" <<
		"    <extensions>\n" <<
		"     <gpxtpx:TrackPointExtension>\n" <<
		"      <gpxtpx:hr>" << hr << "</gpxtpx:hr>\n" <<
		"     </gpxtpx:TrackPointExtension>\n" <<
		"    </extensions>\n" <<
		"   </trkpt>\n";
	return result.str();
}

std::string getFooter() {
	std::stringstream result;
	result << "  </trkseg>\n" <<
		" </trk>\n" <<
		"</gpx>\n";
	return result.str();
}

int main() {
	int hr, totalTime;
	std::cin >> hr >> totalTime;

	std::ofstream outputFile("hr_test.gpx");
	if (!outputFile.is_open()) {
		std::cerr << "Cannot open output";
	}

	outputFile << getHeader();

	int time = 36000;
	double lat = 50.0001;
	double lon = 14.0001;
	for (int i = 0; i <= totalTime / secondsPerSplit; i++) {
		outputFile << getTrackPoint(lat, lon, formatTime(time), hr);
		lon += lonGain;
		time += secondsPerSplit;
	}

	outputFile << getFooter();
	outputFile.close();
    return 0;
}

