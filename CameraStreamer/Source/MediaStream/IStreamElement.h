/**
 * @interface IStreamElement
 * 
 * @brief Defines a common inferface for elements used in stream. This structure
 * 	enforces taking control over the element in opposition to the Bin control
 * 	implemented by Gstreamer.
 *
 * @date Aug 25, 2014
 * @author Aleksander Bulski
 */

#ifndef ISTREAMELEMENT_H_
#define ISTREAMELEMENT_H_

#include <map>
#include <memory>
#include <climits>
#include "gst/gst.h"
#include "StreamElementType.h"
#include "../Exceptions/StreamElementNotCreatedException.h"

class IStreamElement
{
public:
	/**
	 * @brief Retrieves a raw Gstreamer element. IStreamElement is not an
	 * 	owner of the raw element. The
	 * @return Element in a raw type.
	 */
	virtual GstElement* GetRawElement() = 0;

	/**
	 * @brief Returns basic high-level role of the element.
	 * @return Element type as defined in enum.
	 */
	virtual StreamElementType GetType() const = 0;

	/**
	 * @brief Returns a stream the element belongs to.
	 * @return Pointer to GstBin stream object or nullptr if element does not
	 * 	belong to any stream.
	 */
	virtual GstBin* GetStream() = 0;

	/**
	 * @brief Attempts to set params as given in the map.
	 * @param[in] sinkElement Element to link to.
	 * @param[in] params  Map of name-value pairs.
	 * @return True if all parameters set successfuly. False if at least one
	 * 	could not be set (no matching parameter).
	 */
	virtual bool LinkElementUsingParameters(std::shared_ptr<IStreamElement> sinkElement,
				const std::map<std::string, std::string>& params) = 0;

	/**
	 * @brief Links an element that can be a sink to this one.
	 * @param[in] sinkElement Element to stream data into.
	 * @return True if operation succeeded.
	 */
	virtual bool LinkElement(std::shared_ptr<IStreamElement> sinkElement) = 0;

	/**
	 * @brief Unlinks previously linked element from this one.
	 * @param[in] sinkElement Element to unlink from.
	 * @return True if operation succeeded.
	 */
	virtual bool UnlinkElement(std::shared_ptr<IStreamElement> sinkElement) = 0;

	/**
	 * @brief Adds element to the stream.
	 * @param[in] stream Stream to add object into.
	 * @return True if operation succeeded.
	 */
	virtual bool AddToStream(GstBin* stream) = 0;

	/**
	 * @brief Removes element from the stream it was linked to without
	 * 	deleting the element.
	 * @return True if operation succeeded.
	 */
	virtual bool RemoveFromStream() = 0;

	/**
	 * @brief Checks if passed parameter is valid.
	 * @param[in] paramName Parameter name.
	 * @return Type of the parameter value if valid. ULong.max if invalid.
	 */
	virtual GType ValidateParameter(const std::string& paramName) = 0;

	virtual ~IStreamElement() {}
};

#endif /* ISTREAMELEMENT_H_ */
