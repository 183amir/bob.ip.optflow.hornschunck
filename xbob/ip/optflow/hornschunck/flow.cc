/**
 * @file ip/python/flow.cc
 * @date Wed Mar 16 15:01:13 2011 +0100
 * @author Andre Anjos <andre.anjos@idiap.ch>
 *
 * @brief Binds a few Optical Flow methods to python
 *
 * Copyright (C) 2011-2013 Idiap Research Institute, Martigny, Switzerland
 */

#include <bob/ip/HornAndSchunckFlow.h>
#include <bob/python/ndarray.h>
#include <bob/core/cast.h>

using namespace boost::python;

static tuple vanillahs_call(const bob::ip::optflow::VanillaHornAndSchunckFlow& f,
    double alpha, size_t iterations, bob::python::const_ndarray i1,
    bob::python::const_ndarray i2) {
  const bob::core::array::typeinfo& info = i1.type();
  bob::python::ndarray u(bob::core::array::t_float64, info.shape[0], info.shape[1]);
  bob::python::ndarray v(bob::core::array::t_float64, info.shape[0], info.shape[1]);
  blitz::Array<double,2> u_ = u.bz<double,2>();
  u_ = 0;
  blitz::Array<double,2> v_ = v.bz<double,2>();
  v_ = 0;
  switch (info.nd) {
    case bob::core::array::t_uint8:
      f(alpha, iterations, bob::core::array::cast<double,uint8_t>(i1.bz<uint8_t,2>()), 
          bob::core::array::cast<double,uint8_t>(i2.bz<uint8_t,2>()), u_, v_);
      break;
    case bob::core::array::t_float64:
      f(alpha, iterations, i1.bz<double,2>(), i2.bz<double,2>(), u_, v_);
      break;
    default:
      PYTHON_ERROR(TypeError, "vanilla Horn&Schunck operator does not support array with type '%s'", info.str().c_str());
  }
  return make_tuple(u.self(), v.self());
}

static void vanillahs_call2(const bob::ip::optflow::VanillaHornAndSchunckFlow& f,
    double alpha, size_t iterations, bob::python::const_ndarray i1,
    bob::python::const_ndarray i2, bob::python::ndarray u, bob::python::ndarray v) {
  blitz::Array<double,2> u_ = u.bz<double,2>();
  blitz::Array<double,2> v_ = v.bz<double,2>();
  switch (i1.type().dtype) {
    case bob::core::array::t_uint8:
      f(alpha, iterations, bob::core::array::cast<double,uint8_t>(i1.bz<uint8_t,2>()), 
          bob::core::array::cast<double,uint8_t>(i2.bz<uint8_t,2>()), u_, v_);
      break;
    case bob::core::array::t_float64:
      f(alpha, iterations, i1.bz<double,2>(), i2.bz<double,2>(), u_, v_);
      break;
    default:
      PYTHON_ERROR(TypeError, "vanilla Horn&Schunck operator does not support array with type '%s'", i1.type().str().c_str());
  }
}

static object vanillahs_ec2(const bob::ip::optflow::VanillaHornAndSchunckFlow& f,
    bob::python::const_ndarray u, bob::python::const_ndarray v) {
  const bob::core::array::typeinfo& info = u.type();
  bob::python::ndarray error(info);
  blitz::Array<double,2> error_ = error.bz<double,2>();
  f.evalEc2(u.bz<double,2>(), v.bz<double,2>(), error_);
  return error.self();
}

static object vanillahs_eb(const bob::ip::optflow::VanillaHornAndSchunckFlow& f,
    bob::python::const_ndarray i1, bob::python::const_ndarray i2,
    bob::python::const_ndarray u, bob::python::const_ndarray v) {
  const bob::core::array::typeinfo& info = u.type();
  bob::python::ndarray error(info);
  blitz::Array<double,2> error_ = error.bz<double,2>();
  switch (i1.type().dtype) {
    case bob::core::array::t_uint8:
      f.evalEb(bob::core::array::cast<double,uint8_t>(i1.bz<uint8_t,2>()), 
          bob::core::array::cast<double,uint8_t>(i2.bz<uint8_t,2>()), 
          u.bz<double,2>(), v.bz<double,2>(), error_);
      break;
    case bob::core::array::t_float64:
      f.evalEb(i1.bz<double,2>(), i2.bz<double,2>(),
          u.bz<double,2>(), v.bz<double,2>(), error_);
      break;
    default: PYTHON_ERROR(TypeError, "vanilla Horn&Schunck error on brightness operator does not support array with type '%s'", info.str().c_str());
  }
  return error.self();
}

static tuple hs_call(const bob::ip::optflow::HornAndSchunckFlow& f,
    double alpha, size_t iterations, bob::python::const_ndarray i1, 
    bob::python::const_ndarray i2, bob::python::const_ndarray i3) {
  const bob::core::array::typeinfo& info = i1.type();
  bob::python::ndarray u(bob::core::array::t_float64, info.shape[0], info.shape[1]);
  bob::python::ndarray v(bob::core::array::t_float64, info.shape[0], info.shape[1]);
  blitz::Array<double,2> u_ = u.bz<double,2>();
  u_ = 0;
  blitz::Array<double,2> v_ = v.bz<double,2>();
  v_ = 0;
  switch (info.nd) {
    case bob::core::array::t_uint8:
      f(alpha, iterations, bob::core::array::cast<double,uint8_t>(i1.bz<uint8_t,2>()), 
          bob::core::array::cast<double,uint8_t>(i2.bz<uint8_t,2>()), 
          bob::core::array::cast<double,uint8_t>(i3.bz<uint8_t,2>()), u_, v_);
      break;
    case bob::core::array::t_float64:
      f(alpha, iterations, i1.bz<double,2>(), i2.bz<double,2>(), 
          i3.bz<double,2>(), u_, v_);
      break;
    default:
      PYTHON_ERROR(TypeError, "Horn&Schunck operator does not support array with type '%s'", info.str().c_str());
  }
  return make_tuple(u.self(), v.self());
}

static void hs_call2(const bob::ip::optflow::HornAndSchunckFlow& f,
    double alpha, size_t iterations, bob::python::const_ndarray i1, bob::python::const_ndarray i2,
    bob::python::const_ndarray i3, bob::python::ndarray u, bob::python::ndarray v) {
  blitz::Array<double,2> u_ = u.bz<double,2>();
  blitz::Array<double,2> v_ = v.bz<double,2>();
  switch (i1.type().dtype) {
    case bob::core::array::t_uint8:
      f(alpha, iterations, bob::core::array::cast<double,uint8_t>(i1.bz<uint8_t,2>()), 
          bob::core::array::cast<double,uint8_t>(i2.bz<uint8_t,2>()), 
          bob::core::array::cast<double,uint8_t>(i3.bz<uint8_t,2>()), u_, v_);
      break;
    case bob::core::array::t_float64:
      f(alpha, iterations, i1.bz<double,2>(), i2.bz<double,2>(),
          i3.bz<double,2>(), u_, v_);
      break;
    default:
      PYTHON_ERROR(TypeError, "Horn&Schunck operator does not support array with type '%s'", i1.type().str().c_str());
  }
}

static object hs_ec2(const bob::ip::optflow::HornAndSchunckFlow& f,
    bob::python::const_ndarray u, bob::python::const_ndarray v) {
  const bob::core::array::typeinfo& info = u.type();
  bob::python::ndarray error(info);
  blitz::Array<double,2> error_ = error.bz<double,2>();
  f.evalEc2(u.bz<double,2>(), v.bz<double,2>(), error_);
  return error.self();
}

static object hs_eb(const bob::ip::optflow::HornAndSchunckFlow& f,
    bob::python::const_ndarray i1, bob::python::const_ndarray i2, bob::python::const_ndarray i3,
    bob::python::const_ndarray u, bob::python::const_ndarray v) {
  const bob::core::array::typeinfo& info = u.type();
  bob::python::ndarray error(info);
  blitz::Array<double,2> error_ = error.bz<double,2>();
  switch (i1.type().dtype) {
    case bob::core::array::t_uint8:
      f.evalEb(bob::core::array::cast<double,uint8_t>(i1.bz<uint8_t,2>()), 
          bob::core::array::cast<double,uint8_t>(i2.bz<uint8_t,2>()), 
          bob::core::array::cast<double,uint8_t>(i3.bz<uint8_t,2>()),
          u.bz<double,2>(), v.bz<double,2>(), error_);
      break;
    case bob::core::array::t_float64:
      f.evalEb(i1.bz<double,2>(), i2.bz<double,2>(), i3.bz<double,2>(),
          u.bz<double,2>(), v.bz<double,2>(), error_);
      break;
    default: PYTHON_ERROR(TypeError, "Horn&Schunck error on brightness operator does not support array with type '%s'", info.str().c_str());
  }
  return error.self();
}

static object flow_error(bob::python::const_ndarray i1, bob::python::const_ndarray i2,
    bob::python::const_ndarray u, bob::python::const_ndarray v) {
  bob::python::ndarray error(u.type());
  blitz::Array<double,2> error_ = error.bz<double,2>();
  switch (i1.type().dtype) {
    case bob::core::array::t_uint8:
      bob::ip::optflow::flowError(bob::core::array::cast<double,uint8_t>(i1.bz<uint8_t,2>()), 
          bob::core::array::cast<double,uint8_t>(i2.bz<uint8_t,2>()), u.bz<double,2>(),
          v.bz<double,2>(), error_);
      break;
    case bob::core::array::t_float64:
      bob::ip::optflow::flowError(i1.bz<double,2>(), i2.bz<double,2>(), u.bz<double,2>(),
          v.bz<double,2>(), error_);
      break;
    default: PYTHON_ERROR(TypeError, "flow error operator does not support array with type '%s'", i1.type().str().c_str());
  }
  return error.self();
}

static object laplacian_avg_hs_opencv(bob::python::const_ndarray i) {
  bob::python::ndarray o(i.type());
  blitz::Array<double,2> o_ = o.bz<double,2>();
  bob::ip::optflow::laplacian_avg_hs_opencv(i.bz<double,2>(), o_);
  return o.self();
}

static object laplacian_avg_hs(bob::python::const_ndarray i) {
  bob::python::ndarray o(i.type());
  blitz::Array<double,2> o_ = o.bz<double,2>();
  bob::ip::optflow::laplacian_avg_hs(i.bz<double,2>(), o_);
  return o.self();
}

static const char laplacian_avg_hs_opencv_doc[] = "An approximation to the Laplacian (averaging) operator. Using the following (non-separable) kernel for the Laplacian:\n\n[ 0 -1  0]\n[-1  4 -1]\n[ 0 -1  0]\n\nThis is used as the Laplacian operator on OpenCV. To calculate the u_bar value we must remove the central mean and multiply by -1/4, yielding:\n\n[ 0  1/4  0  ]\n[1/4  0  1/4 ]\n[ 0  1/4  0  ]\n\nNote that you will get the WRONG results if you use the Laplacian kernel directly...";

static const char laplacian_avg_hs_doc[] = "An approximation to the Laplacian operator. Using the following (non-separable) kernel:\n\n[-1 -2 -1]\n[-2 12 -2]\n[-1 -2 -1]\n\nThis is used on the Horn & Schunck paper. To calculate the u_bar value we must remove the central mean and multiply by -1/12, yielding:\n\n[1/12 1/6 1/12]\n[1/6   0  1/6 ]\n[1/12 1/6 1/12]\n\nNote that you will get the WRONG results if you use the Laplacian kernel directly...";

void bind_ip_flow() {
  //Horn & Schunck 
  class_<bob::ip::optflow::VanillaHornAndSchunckFlow>("VanillaHornAndSchunckFlow", "Calculates the Optical Flow between two sequences of images (i1, the starting image and i2, the final image). It does this using the iterative method described by Horn & Schunck in the paper titled \"Determining Optical Flow\", published in 1981, Artificial Intelligence, Vol. 17, No. 1-3, pp. 185-203. Parameters: i1 -- first frame, i2 -- second frame, (u,v) -- estimates of the speed in x,y directions (zero if uninitialized)", init<const blitz::TinyVector<int,2>&>((arg("self"), arg("shape")), "Initializes the vanilla Horn&Schunck operator with the size of images to be fed"))
      .def("__call__", &vanillahs_call, (arg("self"), arg("alpha"), arg("iterations"), arg("image1"), arg("image2")))
      .def("__call__", &vanillahs_call2, (arg("self"), arg("alpha"), arg("iterations"), arg("image1"), arg("image2"), arg("u"), arg("v")))
      .def("eval_ec2", &vanillahs_ec2, (arg("self"), arg("u"), arg("v")), "Calculates the square of the smoothness error (Ec^2) by using the formula described in the paper: Ec^2 = (u_bar - u)^2 + (v_bar - v)^2. Sets the input matrix with the discrete values.")
      .def("eval_eb", &vanillahs_eb, (arg("self"), arg("i1"), arg("i2"), arg("u"), arg("v")), "Calculates the brightness error (Eb) as defined in the paper: Eb = (Ex*u + Ey*v + Et). Sets the input matrix with the discrete values")
      ;

  class_<bob::ip::optflow::HornAndSchunckFlow>("HornAndSchunckFlow", "This is a clone of the Vanilla HornAndSchunck method that uses a Sobel gradient estimator instead of the forward estimator used by the classical method. The Laplacian operator is also replaced with a more common method.", init<const blitz::TinyVector<int,2>&>((arg("self"), arg("shape")), "Initializes the vanilla Horn&Schunck operator with the size of images to be fed"))
      .def("__call__", &hs_call, (arg("self"), arg("alpha"), arg("iterations"), arg("image1"), arg("image2"), arg("image3")))
      .def("__call__", &hs_call2, (arg("self"), arg("alpha"), arg("iterations"), arg("image1"), arg("image2"), arg("image3"), arg("u"), arg("v")))
      .def("eval_ec2", &hs_ec2, (arg("self"), arg("u"), arg("v")), "Calculates the square of the smoothness error (Ec^2) by using the formula described in the paper: Ec^2 = (u_bar - u)^2 + (v_bar - v)^2. Sets the input matrix with the discrete values.")
      .def("eval_eb", &hs_eb, (arg("self"), arg("i1"), arg("i2"), arg("i3"), arg("u"), arg("v")), "Calculates the brightness error (Eb) as defined in the paper: Eb = (Ex*u + Ey*v + Et). Sets the input matrix with the discrete values")
      ;

  def("laplacian_avg_hs_opencv", &laplacian_avg_hs_opencv, (arg("input")), laplacian_avg_hs_opencv_doc);
  def("laplacian_avg_hs", &laplacian_avg_hs, (arg("input")), laplacian_avg_hs_doc);

  def("flow_error", &flow_error, (arg("i1"), arg("i2"), arg("u"), arg("v")), "Computes the generalized flow error: E = i2(x-u,y-v) - i1(x,y))");
}
