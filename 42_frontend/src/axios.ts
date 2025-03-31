import axios from "axios";
import Swal from "sweetalert2";

export const $ = axios.create({
  baseURL: "http://localhost:2424",
  headers: {
    "Content-Type": "application/json",
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
      error.response.data.redirect &&
      error.response.data.redirect.redirect_url
    ) {
      window.location.href = `http://localhost:2424${error.response.data.redirect.redirect_url}`;
      // navigate(error.response.data.redirect.redirect_url, { replace: true });
    } else if (error.response.dat4a.redirect_url)
      window.location.href = `http://localhost:2424${error.response.data.redirect_url}`;

    return Promise.reject(error);
  }
);
