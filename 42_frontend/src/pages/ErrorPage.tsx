import { useEffect } from "react";
import { Outlet, useNavigate } from "react-router-dom";
import { $ } from "../axios";

const ErrorPage = () => {
  console.log("default error page");
  const navigate = useNavigate();
  const whatError = async () => {
    const response = await $.get("/api/error").then((res) => res.data);
    console.log("ErrorPage");
    console.log(response);
    if (response.redirect.redirect_url)
      navigate(response.redirect.redirect_url);
  };
  useEffect(() => {
    whatError();
  }, []);

  return (
    <div>
      <Outlet />
      <div>ErrorPage</div>
    </div>
  );
};

export default ErrorPage;
