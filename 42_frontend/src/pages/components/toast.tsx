import { ReactNode } from "react";
import { toast, ToastOptions } from "react-toastify";
// import styled from "styled-components";
import "./toast.css";
// import { ToastContainer as ReactToastContainer } from 'react-toastify';

// export const StyledToastContainer = styled(ReactToastContainer)`
//   margin-top: 60px;
//   .Toastify__toast {
//     background-color: #0FFFFF;
//     color: #FFFFFF;
//   }
//   .Toastify__toast--info {
//     border: 1px solid transparent;
//   }
//   .Toastify__toast--success {
//     border: 1px solid #FF0FFF;
//   }
//   .Toastify__toast--error {
//     border: 1px solid #FFFF0F;
//   }
// `;

const defaultToastOption: ToastOptions = {
  position: "top-right",
  autoClose: 4000,
  hideProgressBar: true,
  closeOnClick: true,
  draggable: true,
  pauseOnHover: false,
  closeButton: false,
};

export const Toast = {
  info: (message: ReactNode, options: ToastOptions = {}) => {
    toast.info(message, { ...defaultToastOption, ...options });
  },
  success: (message: ReactNode, options: ToastOptions = {}) => {
    toast.success(message, { ...defaultToastOption, ...options });
  },
  error: (message: ReactNode, options: ToastOptions = {}) => {
    toast.error(message, { ...defaultToastOption, ...options });
  },
};
