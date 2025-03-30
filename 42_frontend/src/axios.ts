import axios from "axios";
// import { useNavigate } from "react-router-dom";
import Swal from "sweetalert2";

// const sessionId =
//   sessionStorage.getItem("sessionid") || localStorage.getItem("sessionid");
// const navigate = useNavigate();

export const $ = axios.create({
  baseURL: "http://localhost:2424",
  headers: {
    "Content-Type": "application/json",
    // Authorization: `Bearer ${sessionId}`,
  },
});

$.interceptors.response.use(
  (response) => {
    return response;
  },
  (error) => {
    console.log("here error!!!!");
    console.error(error.response);
    if (error.response.status === 401) {
      Swal.fire({
        icon: "error",
        title: "",
        text: "userid 재입력이 필요합니다!",
        confirmButtonText: "닫기",
      }).then(() => {
        window.location.href = `http://localhost:2424/main`;
      });
    } else if (
      error.response.data.redirec &&
      error.response.data.redirect.redirect_url
    ) {
      window.location.href = `http://localhost:2424${error.response.data.redirect.redirect_url}`;
      // navigate(error.response.data.redirect.redirect_url, { replace: true });
    }
    return Promise.reject(error);
  }
);
