//  extended-scanner.hpp -- devices that handle extended commands
//  Copyright (C) 2012  SEIKO EPSON CORPORATION
//
//  License: GPL-3.0+
//  Author : AVASYS CORPORATION
//
//  This file is part of the 'Utsushi' package.
//  This package is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License or, at
//  your option, any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//  You ought to have received a copy of the GNU General Public License
//  along with this package.  If not, see <http://www.gnu.org/licenses/>.

#ifndef drivers_esci_extended_scanner_hpp_
#define drivers_esci_extended_scanner_hpp_

#include <utsushi/connexion.hpp>
#include <utsushi/octet.hpp>

#include "bounding-box.hpp"
#include "chunk.hpp"
#include "get-extended-identity.hpp"
#include "get-scanner-status.hpp"
#include "point.hpp"
#include "scanner.hpp"
#include "set-scan-parameters.hpp"
#include "start-extended-scan.hpp"

#define start_extended_scan start_ext_scan_alloc

namespace utsushi {
namespace _drv_ {
namespace esci {

class extended_scanner : public scanner
{
public:
  extended_scanner (const connexion::ptr& cnx);

  void configure ();

  virtual bool is_single_image () const;

protected:
  bool set_up_sequence ();
  bool is_consecutive () const;
  bool obtain_media ();
  bool set_up_image ();
  void finish_image ();
  streamsize sgetn (octet *data, streamsize n);

private:
  get_extended_identity capability_;
  get_scanner_status    dev_status_;
  set_scan_parameters   parameters_;
  start_extended_scan   acquire_;

  chunk  chunk_;
  streamsize offset_;

  source_value src_;
  point<uint32_t> res_;
  bounding_box<uint32_t> area_;
  short color_mode_;
  short bit_depth_;
  uint8_t line_count_;
};

}       // namespace driver
}       // namespace _drv_
}       // namespace utsushi

#endif  /* drivers_esci_extended_scanner_hpp_ */