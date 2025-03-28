import axios from "axios";
import Swal from "sweetalert2";

// const sessionId =
//   sessionStorage.getItem("sessionid") || localStorage.getItem("sessionid");

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
    if (error.response.status === 401) {
      Swal.fire({
        icon: "error",
        title: "",
        text: "userid 재입력이 필요합니다!",
        confirmButtonText: "닫기",
      }).then(() => {
        window.location.href = `locahost:2424/main`;
      });
    } else if (error.response.data.redirect.redirect_url) {
      window.location.href = `locahost:2424/${error.response.data.redirect.redirect_url}`;
    }
    return Promise.reject(error);
  }
);
