/**
 * @struct CameraCapsRecord
 * 
 * @brief Holds a valid camera parameters set.
 *
 * @date Aug 20, 2014
 * @author Aleksander Bulski
 */

#ifndef CAMERACAPSRECORD_H_
#define CAMERACAPSRECORD_H_

#include <string>
#include <set>
#include <map>

typedef std::string VideoFormat;
typedef std::set<std::string> AvailableFramerates;

class CameraCapsRecord
{
public:
	unsigned short height;
	unsigned short width;
	std::map<VideoFormat, AvailableFramerates> videoFormats;

	bool operator<(const CameraCapsRecord& record) const
	{
		if(width == record.width)
		{
			return height < record.height;
		}

		return width < record.width;
	}
};

#endif /* CAMERACAPSRECORD_H_ */
