//  pump.hpp -- move image octets from a source to a sink
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

#ifndef utsushi_pump_hpp_
#define utsushi_pump_hpp_

#include <csignal>

#include "device.hpp"
#include "log.hpp"
#include "option.hpp"
#include "signal.hpp"
#include "stream.hpp"
#include "thread.hpp"

namespace utsushi {

//! Move image octets from a source to a sink
class pump
  : public configurable
{
public:
  typedef shared_ptr< pump > ptr;

  pump (idevice::ptr idev);
  pump (istream::ptr istr);

  virtual ~pump ();

  virtual void start (odevice::ptr odev);
  virtual void start (ostream::ptr ostr);

  void cancel ();

  typedef signal< void (log::priority, std::string) > notify_signal_type;

  connection connect (const notify_signal_type::slot_type& slot) const;

protected:
  void start_(output::ptr optr);
  void acquire_();
  void require_(input::ptr iptr);
  void require_(output::ptr optr);

  input::ptr  iptr_;
  output::ptr optr_;

  //! \todo Replace with query on iptr_?
  sig_atomic_t is_cancelling_;
  sig_atomic_t is_pumping_;

  thread *thread_;

  mutable notify_signal_type signal_notify_;
};

}       // namespace utsushi

#endif  /* utsushi_pump_hpp_ */