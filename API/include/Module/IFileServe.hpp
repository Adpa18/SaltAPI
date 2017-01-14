//
// Created by wery_a on 07/01/17.
//

#ifndef API_V2_IFILESERVE_HPP
#define API_V2_IFILESERVE_HPP

#include <string>
#include <fstream>

namespace Module {
    /*! @class IFileServer
     * Interface serving file of system
     */
    class IFileServe {
    public:
        virtual ~IFileServe() {}
        
        /*! @fn unsigned int GetFileSize(std::string const &path) const
         *
         * @param path of file
         * @return size of the file
         */
        virtual unsigned int GetFileSize(std::string const &path) const = 0;

        /*! @fn std::ifstream &GetFile(std::string const &path) const
        *
        * @param path of file
        * @return return std::ifstream of the opened file
        */
        virtual std::ifstream &GetFile(std::string const &path) const = 0;

        /*! @fn char *GetFileByRange(unsigned int offset, unsigned int size) const
         *
         * @param offset
         * @param size
         * @return data read in the range [offset, offset + size]
         */
        virtual char *GetFileByRange(unsigned int offset, unsigned int size) const = 0;
    };
}
#endif //API_V2_IFILESERVE_HPP
