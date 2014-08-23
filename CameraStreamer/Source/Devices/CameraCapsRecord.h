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

struct CameraCapsRecord
{
public:
	unsigned short height;
	unsigned short width;
	std::string format;
	std::string pixelAspectRatio;
	std::set<std::string> framerates;

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
