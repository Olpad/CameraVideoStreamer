/**
 * @class ISystemService
 * 
 * @brief Interface for system services which will have global access
 * 	and are initialized at the start of the application.
 *
 * @date Aug 21, 2014
 * @author Aleksander Bulski
 */

#ifndef ISYSTEMSERVICE_H_
#define ISYSTEMSERVICE_H_

class ISystemService
{
public:
	virtual void Initialize() = 0;

	virtual ~ISystemService() {}
};

#endif /* ISYSTEMSERVICE_H_ */
