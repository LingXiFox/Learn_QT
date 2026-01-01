#ifndef NCM_H
#define NCM_H

#include <filesystem>
#include <string>

namespace ncm {

bool process_ncm_file(const std::filesystem::path& file_path,
                      std::string* out_message = nullptr);

bool process_ncm_folder(const std::filesystem::path& folder_path,
                        std::string* out_message = nullptr);

} // namespace ncm

#endif
